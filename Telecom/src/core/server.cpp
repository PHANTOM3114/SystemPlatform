#include "server.h"

server::server()
{
    port = find_available_port(START_PORT, END_PORT);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Creating socket error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bound error!");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, BACKLOG))
    {
        perror("Listening error!");
        exit(EXIT_FAILURE);
    }
    
}

server::~server()
{
    close(server_fd);
}

void server::start() {
    std::cout << "Listening PORT " << port << std::endl;

    struct sockaddr_in client_addr {};
    socklen_t client_len = sizeof(client_addr);

    while (true) {
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

        if (client_fd < 0) {
            perror("Accepting connection error!");
            continue;
        }

        std::cout << "Client connecting " << inet_ntoa(client_addr.sin_addr) << std::endl;

        // Використовуємо лямбда-функцію для створення потоку
        std::thread client_thread([this, client_fd]() {
            this->handle_client(client_fd);
        });
        client_thread.detach();
    }
}

void* server::handle_client(int client_socket)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';
        std::cout << "Received " << buffer << std::endl;
    }

    std::cout << "Client has disconnected\n";
    close(client_socket);
}

int server::find_available_port(int start_port, int end_port)
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock_fd == -1)
    {
        std::cerr << "Error creating socket\n";
        return -1;
    }

    struct sockaddr_in addr {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 0;

    if (bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        std::cerr << "Error binding socket!\n";
        return -1;
    }

    socklen_t addr_len = sizeof(addr);

    if (getsockname(sock_fd, (struct sockaddr*)&addr, &addr_len) == -1)
    {
        std::cerr << "Error getting socket name!\n";
        close(sock_fd);
        return -1;
    }

    int free_port = ntohs(addr.sin_port);
    close(sock_fd);
    return free_port;
}