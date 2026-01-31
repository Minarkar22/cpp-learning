#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

std::string get_response(const std::string &request);

int main(){
   // create socket
   int server_socket = socket(AF_INET, SOCK_STREAM, 0);
   if (server_socket == -1) {
      std::cerr << "Failed to create socket!\n";
      return 1;
   }

   //Specify address and port
   struct sockaddr_in server_address{};
   server_address.sin_family = AF_INET;
   server_address.sin_port = htons(9002);
   server_address.sin_addr.s_addr = INADDR_ANY;

   int opt = 1;
   setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));


   //Bind addr and port 
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

   std::cout << "Tiny HTTP Server is listening at http://localhost:9002 ...\n";

   while (true) {
      //For Client socket
      struct sockaddr_in client_address{};
      socklen_t addrlen = sizeof(client_address);

      int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &addrlen);
      if (client_socket == -1){
         std::cerr << "Failed Accept!\n";
         continue;
      }

      //Receive data from client
      char buffer[4096] = {};
      ssize_t byte_receives = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
      if (byte_receives > 0){
         buffer[byte_receives] = '\0'; //Add null character at the end to become C string

         std::string request(buffer); // Convert to C++ string - Copy the content of buffer into request variable

         std::cout << "Received request:\n" << request << "\n";

         std::string response = get_response(request);

         send(client_socket, response.c_str(), response.size(), 0);
      }
      close(client_socket);
   }

   close(server_socket);

   return 0;
}

std::string get_response(const std::string &request){
   std::string body =
        "<html>"
        "<h1>Hello from my HTTP Server</h1>"
        "</html>";

    std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " + std::to_string(body.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" +
        body;
   return response;
}