#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <sys/select.h>
#include <sstream>


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

   //Create fd_set
   fd_set master;  //all sockets we track
   FD_ZERO(&master);
   FD_SET(server_socket, &master);
   int fd_max = server_socket;

   while (true){
        fd_set copy = master;
        if (select(fd_max + 1,&copy, nullptr,nullptr, nullptr) == -1){
            std::cerr << "Select error!\n";
            break;
        }

        for (int fd = 0; fd <= fd_max; fd++){
            if (FD_ISSET(fd, &copy)){
                if (fd == server_socket){
                    //Accept a new connection
                    sockaddr_in client_address{};
                    socklen_t len = sizeof(client_address);
                    int new_fd = accept(fd,(struct sockaddr *)&client_address, &len);

                    //Add a new connection to the list of connected clients
                    FD_SET(new_fd, &master);
                    if (new_fd > fd_max) fd_max = new_fd;

                    //Send a welcome message to connected clients
                    std::string welcomeMsg = "Welcome to Awsome Chat Server!\r\n";
                    send(new_fd,welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
                }else{
                    //Accept a new message
                    //Send message to other clients
                    char buff[4096];
                    int bytesIn = recv(fd,buff, sizeof(buff) -1, 0);
                    if (bytesIn <= 0){
                        //Drop the client
                        close(fd);
                        FD_CLR(fd, &master);
                    }else {
                        //send message to other clients
                        buff[4096] = '\0';

                        for (int outSock = 0; outSock <= fd_max; outSock++){
                            if (FD_ISSET(outSock, &master)){
                                if (outSock != server_socket && outSock != fd){
                                    std::ostringstream ss;
                                    ss << "SOCKET #" << fd << ": " << buff << "\r\n\n";
                                    std::string strOut = ss.str();
                                    send(outSock, strOut.c_str(), strOut.size() + 1, 0);
                                }
                            }
                        }
                
                    }
                }
            }
        }

   }
}