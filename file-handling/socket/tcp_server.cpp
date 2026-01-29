#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main()
{
    //create server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //specify the socket address and port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //bind socket to specified IP and Port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(server_socket, 5);

    std::cout << "Server is listening at port 9002 ...\n";

    //create client socket that is borned from accept()
    //int client_socket = accept(server_socket, nullptr, nullptr);
    int client_socket;

    struct sockaddr_in client_address;
    socklen_t addrlen = sizeof(client_address);

    client_socket = accept(server_socket, (struct sockaddr*) &client_address, &addrlen);

    //receive data from client
    char client_request[1024];
    ssize_t n = recv(client_socket, client_request, sizeof(client_request) - 1, 0);

    // response from server
    const char* msg = "Hello client from Server!\n"; 
    if (n > 0){
        client_request[n] = '\0';
        std::cout << "Received : " << client_request << std::endl;
        send(client_socket, msg, strlen(msg), 0);
    }

    //close sockets
    
    close(client_socket);
    //close(server_socket);

    return 0;
}