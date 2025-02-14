#include "client.h"

int read_port()
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

int main(int argc, char* argv[])
{

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in socket_addr {};
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ЯВНО прописати localhost
    socket_addr.sin_port = htons(read_port());

    if (sock_fd < 0)
    {
        perror("Error creating socket!");
        exit(EXIT_FAILURE);
    }

    if (connect(sock_fd, (struct sockaddr*)&socket_addr, sizeof(socket_addr)) < 0)
    {
        perror("Connection failed!");
        exit(EXIT_FAILURE);
    }

    std::cout << "Connecting was successfully!" << std::endl;

    std::string message = "Hello Pidar!";

    send(sock_fd, message.c_str(), message.size(), 0);
    
    std::cout << "message was sent successfully!" << std::endl;

    return 0;
}