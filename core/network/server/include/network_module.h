#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <thread>
#include <nlohmann/json.hpp>
#include <asio.hpp>
#include <database_datamodule.h>

#define START_PORT 8000
#define END_PORT 9000
#define BACKLOG 5
#define BUFFER_SIZE 1024

namespace Core {
    namespace Network {

class network_module
{
private:

    int port;
    int server_fd;
    void* handle_client(int client_socket);
    DataModule& data_module;

public:

    network_module(DataModule& dataModule);
    ~network_module();

    void start();
    int find_available_port(int start_port, int end_port);
};

    }
}