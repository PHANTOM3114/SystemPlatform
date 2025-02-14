#include "client.h"
#include "connection.h"

Client::Client() {};

int Client::read_port()
{
    std::filesystem::path relativePath = "../../data/server_port.txt";
    std::filesystem::path absolute = std::filesystem::absolute(relativePath);
    
    std::ifstream file(relativePath);
    int port = 0;

    if (file.is_open())
    {
        file >> port;
        file.close();
    }

    else
    {
        std::cerr << "Error while opening file: " << relativePath << std::endl;
        exit(EXIT_FAILURE);
    }

    if (port <= 0 || port > 65535)
    {
        std::cerr << "Invalid port number!" << std::endl;
        exit(EXIT_FAILURE);
    }

    return port;
}

void Client::run() {
    Connection conn(read_port());
    conn.connect_to_server();
    conn.send_message("Hello World!");
}