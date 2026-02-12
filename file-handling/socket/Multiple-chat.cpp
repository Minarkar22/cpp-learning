#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <sys/select.h>
#include <sstream>
#include <map>
#include <string>


int main(){
    //1. Create server
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1){
        std::cerr << "Failed to create socket!\n";
        return 1;
    }

    struct sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1){
        std::cerr << "Bind Failed!\n";
        close(server_socket);
        return 1;
   }

    if (listen(server_socket, 5) == -1){
      std::cerr << "Failed to Listen!\n";
      close(server_socket);
      return 1;
   }

   std::cout << "Server listening on port 9002...\n";

   //Create fd_set
   fd_set master;  //all sockets we track
   FD_ZERO(&master);
   FD_SET(server_socket, &master);
   int fd_max = server_socket;

   //fd - username after login
   std::map<int, std::string> clients;

   //fd - pending username buffer
   std::map<int, std::string> pending;

   while (true){
        fd_set copy = master;
        if (select(fd_max + 1,&copy, nullptr,nullptr, nullptr) == -1){
            std::cerr << "select() error!\n";
            break;
        }

        for (int fd = 0; fd <= fd_max; fd++){
            if(!FD_ISSET(fd, &copy)) continue;

            if (FD_ISSET(fd, &copy)){
                if (fd == server_socket){
                    //Accept a new connection
                    sockaddr_in client_address{};
                    socklen_t addr_len = sizeof(client_address);
                    int new_fd = accept(fd,(struct sockaddr *)&client_address, &addr_len);

                    if(new_fd == -1){
                        std::cerr << "accept() failed\n";
                        continue;
                    }
                    std::cout << "New connection: fd = " << new_fd << "\n";

                    //Add a new connection to the list of connected clients
                    FD_SET(new_fd, &master);
                    if (new_fd > fd_max) fd_max = new_fd;

                    //Send a welcome message to connected clients
                    std::string welcomeMsg = "Welcome to Awsome Chat Server!\r\n"
                                             "Please enter your username: ";
                    send(new_fd,welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);

                    //Mark as pending user
                    pending[new_fd] = "";
                }else{
                    //Accept a new message
                    //Send message to other clients
                    char buff[4096];
                    memset(buff, 0, sizeof(buff));  //For safer
                    
                    int bytesIn = recv(fd,buff, sizeof(buff) -1, 0);
                    if (bytesIn <= 0){
                        //Drop the client
                        std::cout << "Client disconnected: fd = " << fd << "\n";

                        if (clients.count(fd)){
                            std::string left_msg = "[" + clients[fd] + "] has left the chat.\r\n";
                            for (int other = 0; other <= fd_max; ++other) {
                                if (FD_ISSET(other, &master) && other != server_socket && other != fd) {
                                    send(other, left_msg.c_str(), left_msg.size(), 0);
                                }
                            }
                        }
                        close(fd);
                        FD_CLR(fd, &master);
                        clients.erase(fd);
                        pending.erase(fd);
                        continue;
                    }

                    
                    buff[bytesIn] = '\0';  //null terminated

                    //Checking pending username
                    if (pending.count(fd)) {
                        std::string name = buff;
                        while (!name.empty() && (name.back() == '\n' || name.back() == '\r'))
                            name.pop_back();
                        if (name.empty()) {
                            send(fd, "Username cannot be empty. Try again: ", 38, 0);
                            continue;
                        }

                        clients[fd] = name;
                        pending.erase(fd);

                        std::string ok = "Hello " + name + "! You can start chatting.\r\n";
                        send(fd, ok.c_str(), ok.size(), 0);

                        //Announce Join
                        std::string join_msg = "[" + name + "] has joined the chat!\r\n";
                        for (int other = 0; other <= fd_max; ++other) {
                            if (FD_ISSET(other, &master) && other != server_socket && other != fd) {
                                send(other, join_msg.c_str(), join_msg.size(), 0);
                            }

                        }
                        continue;
                    }
                    //Normal chat message
                    if (!clients.count(fd)) continue;

                    std::string username = clients[fd];
                    std::string message = buff;

                    while (!message.empty() && (message.back() == '\n' || message.back() == '\r'))
                        message.pop_back();
                    
                    if (message.empty()) continue;

                    std::string formatted = "[" + username + "] " + message + "\r\n";

                    //Broadcast
                    for (int other = 0; other <= fd_max; ++other){
                        if (FD_ISSET(other, &master) && other != server_socket) {
                            send(other, formatted.c_str(), formatted.size(), 0);
                        }
                    }
                }
            }
        }

   }

   close(server_socket);
   return 0;
}