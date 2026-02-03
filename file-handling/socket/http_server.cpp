#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <fstream>
#include <filesystem>

std::string get_response(const std::string &request);
std::string serve_file(const std::string &path);

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

std::string serve_file(const std::string &path){
   std::string doc_root = "./www"; //add real file path

    // Prevent directory traversal
   if (path.find("..") != std::string::npos) {
      return "HTTP/1.1 403 Forbidden\r\nContent-Length: 0\r\n\r\n";
   }

   std::string file_path = (path == "/") ? doc_root + "/index.html" : doc_root + path ;

   if (!std::filesystem::exists(file_path)){
      std::string body = "<h1>404 Not Found</h1>";
      return   
         "HTTP/1.1 404 Not Found\r\n"
         "Content-Type: text/html\r\n"
         "Content-Length: " + std::to_string(body.size()) + "\r\n\r\n"
         + body;
   }

   std::ifstream file(file_path, std::ios::binary);
   
   std::string body(
      (std::istreambuf_iterator<char>(file)),
      std::istreambuf_iterator<char>()
   );

   std::string mime = "text/html";
   if (file_path.size() >= 4 && file_path.substr(file_path.size()-4) == ".css")
    mime = "text/css";
   if (file_path.size() >= 4 && file_path.substr(file_path.size()-4) == ".js")
    mime = "application/javascript";
   if (file_path.size() >= 4 && file_path.substr(file_path.size()-4) == ".png")
    mime = "image/png";
   if (file_path.size() >= 4 && file_path.substr(file_path.size()-4) == ".jpeg")
    mime = "image/jpeg";
   if (file_path.size() >= 4 && file_path.substr(file_path.size()-4) == ".txt")
    mime = "text/plain";
   
   
   return "HTTP/1.1 200 OK\r\n"
           "Content-Type: " + mime + "\r\n"
           "Content-Length: " + std::to_string(body.size()) + "\r\n"
           "Connection: close\r\n\r\n"
           + body;
}

std::string get_response(const std::string &request){
   size_t pos = request.find("\r\n");
   if (pos == std::string::npos){
      return "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
   }

   std::string first_line = request.substr(0, pos);
   std::string method, path, version;

   size_t sp1 = first_line.find(' ');
   size_t sp2 = first_line.find(' ', sp1 + 1);

   if (sp1 == std::string::npos || sp2 == std::string::npos){
      return "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
   }

   method = first_line.substr(0, sp1);
   path = first_line.substr(sp1 + 1, sp2 - sp1 -1);
   version = first_line.substr(sp2 + 1);

   if (method != "GET"){
      return "HTTP/1.1 405 Method Not Allowed\r\nContent-Length: 0\r\n\r\n";
   }

   // std::string body;
   // std::string status = "200 OK";

   // if (path == "/" || path == "/index.html"){
   //    body =
   //      "<!DOCTYPE html>\n"
   //       "<html><head><title>Tiny Server</title></head>\n"
   //       "<body><h1>Hello from my tiny C++ HTTP server!</h1>\n"
   //       "<p>Try going to <a href=\"/about\">/about</a></p></body></html>";
   // } else {
   //    status = "404 Not Found";
   //    body = 
   //       "<!DOCTYPE html>\n"
   //       "<html><body><h1>404 - Not Found</h1>\n"
   //       "<p>Sorry, that page does not exist.</p></body></html>";
   // }


   return serve_file(path);

   

// std::string response =
//       "HTTP/1.1 " + status + "\r\n"
//       "Content-Type: text/html; charset=utf-8\r\n"
//       "Content-Length: " + std::to_string(body.size()) + "\r\n"
//       "Connection: close\r\n"
//       "\r\n" +
//       body;
//    return response;
}