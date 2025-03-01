//
// Created by Mykhailo Khymochko on 27.02.25.
//

#ifndef NETWORK_MODULE_H
#define NETWORK_MODULE_H

#include <asio.hpp>
#include <config.h>
#include <cstdlib>
#include <cstring>
#include <database_datamodule.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <thread>
#include <unistd.h>
#include <arpa/inet.h>
#include <nlohmann/json.hpp>

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

#endif //NETWORK_MODULE_H
