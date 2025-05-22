#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd < 0) {
        std::cout << "Error creating socket.";
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6379);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if(connect(client_fd, (sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return 1;
    }

    const char* msg = "PING\r\n";
    send(client_fd, msg, strlen(msg), 0);

    char buffer[4096] = {};
    recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    std::cout << "Server says: " << buffer << "\n";

    close(client_fd);
    return 0;
}
