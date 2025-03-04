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
#include <ctime>

#define START_PORT 8000
#define END_PORT 9000
#define BACKLOG 5
#define BUFFER_SIZE 1024

namespace Core
{
    namespace Network {

class network_module
{
private:

    int port;
    int server_fd;
    void* handle_client(int client_socket);
    
    // Client-side fields
    int max_connections;
    int current_active_connections;

public:

    network_module();
    ~network_module();

    void start();
    int find_available_port(int start_port, int end_port);
    
    // Client to server requests
    void request_handler(int client_socket, const std::string& message);
    
    std::string get_time();
    std::string get_status();
    
    void send_responce(int client_socket, const std::string& responce);
    
    // Getters and setters
    int get_max_connections() const { return max_connections; };
    void set_max_connections(int max_connections) { this->max_connections = max_connections; };
    
    int get_current_active_connections() { return current_active_connections; };
    void set_current_active_connections(int current_active_connections) { this->current_active_connections = current_active_connections; };
};

    }
}
