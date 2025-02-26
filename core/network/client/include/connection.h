#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class Connection {
private:
    int sock_fd;
    struct sockaddr_in socket_addr;

public:
    explicit Connection(int port);
    ~Connection();
    void connect_to_server();
    void send_message(const std::string& message);
};