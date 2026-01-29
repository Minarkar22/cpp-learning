#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main(){
	
	//create socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	//specify the socket address and port
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	//server_address.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

	//connect to server
	int connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

	if (connection_status < 0){
		std::cout << "Error in conection!\n";
		return 1;
	}

	std::cout << "Connecting to Server ... \n";

	//send message to Server
	const char* message = "Hi from client!\n";
    send(network_socket, message, strlen(message), 0);

	//receive data from server
	char server_response[1024];
	ssize_t n = recv(network_socket, server_response, sizeof(server_response) - 1, 0);

	//print out the data, we get back from server
	if (n > 0) {
    server_response[n] = '\0';
    std::cout << "The server sent the data: " << server_response << std::endl;
	}

	//and then close socket
	close(network_socket);
	return 0;
}
