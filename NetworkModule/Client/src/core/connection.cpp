#include "connection.h"

Connection::Connection(int port) {
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Error creating socket!");
        exit(EXIT_FAILURE);
    }

    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socket_addr.sin_port = htons(port);
}

Connection::~Connection() {
    close(sock_fd);
}

void Connection::connect_to_server() {
    if (connect(sock_fd, (struct sockaddr*)&socket_addr, sizeof(socket_addr)) < 0) {
        perror("Connection failed!");
        exit(EXIT_FAILURE);
    }
    std::cout << "Connecting was successful!" << std::endl;
}

void Connection::send_message(const std::string& message) {
    send(sock_fd, message.c_str(), message.size(), 0);
    std::cout << "Message was sent successfully!" << std::endl;
}