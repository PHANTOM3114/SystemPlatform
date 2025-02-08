#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <thread>

#define START_PORT 8000
#define END_PORT 9000
#define BACKLOG 5
#define BUFFER_SIZE 1024

class server
{
private:

    int port;
    int server_fd;
    static void* handle_client(int client_socket);

public:

    server();
    ~server();

    void start();
    int find_available_port(int start_port, int end_port);
};
