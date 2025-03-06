#include "client.h"
#include "connection.h"

Client::Client() {};

int Client::read_port()
{
    std::filesystem::path basePath = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path().parent_path();
    std::filesystem::path absolute = basePath / "data/server_port.txt";
    
    std::ifstream file(absolute);
    int port = 0;
    
    std::cout << "Reading port from: " << absolute << std::endl;

    if (file.is_open())
    {
        file >> port;
        file.close();
    }

    else
    {
        std::cerr << "Error while opening file: " << absolute << std::endl;
        exit(EXIT_FAILURE);
    }

    if (port <= 0 || port > 65535)
    {
        std::cerr << "Invalid port number!" << std::endl;
        exit(EXIT_FAILURE);
    }

    return port;
}

void Client::run()
{
    Connection conn(read_port());
    conn.connect_to_server();
    conn.send_message();
}
