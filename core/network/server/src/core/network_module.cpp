#include "network_module.h"

Core::Network::network_module::network_module()
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

Core::Network::network_module::~network_module()
{
    close(server_fd);
}

void Core::Network::network_module::start()
{
    std::cout << "Listening PORT " << port << std::endl;

    struct sockaddr_in client_addr {};
    socklen_t client_len = sizeof(client_addr);

    while (true)
    {
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

        if (client_fd < 0)
        {
            perror("Accepting connection error!");
            continue;
        }

        std::cout << "Client connecting " << inet_ntoa(client_addr.sin_addr) << std::endl;

        // Use lambda-function for creating the thread
        std::thread client_thread([this, client_fd]() {
            this->handle_client(client_fd);
        });
        client_thread.detach();
    }
}

void* Core::Network::network_module::handle_client(int client_socket)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while (true)
    {
        bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0);

        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0';
            std::cout << "Received " << buffer << std::endl;

            std::string received_message(buffer);
            request_handler(client_socket, received_message);
        }
        else if (bytes_read == 0)
        {
            std::cout << "Client has disconnected\n";
            break;
        }
        else
        {
            perror("Error reading from client!");
            break;
        }
    }

    std::cout << "Closing client socket.\n";
    close(client_socket);

    std::cout << "Client socket closed.\n";
    return nullptr;
}

int Core::Network::network_module::find_available_port(int start_port, int end_port)
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

    std::filesystem::path basePath = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path().parent_path(); 
    std::filesystem::path absolute = basePath / "data/server_port.txt";

    std::cout << "Trying to open file at: " << absolute << std::endl;

    std::ofstream port_file(absolute, std::ios::trunc);

    if (!std::filesystem::exists(absolute))
    {
        std::cerr << "File does not exist! Trying to create..." << std::endl;
        std::ofstream create_file(absolute);
        if (!create_file)
        {
            std::cerr << "Failed to create file! Check permissions!" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    if (port_file.is_open())
    {
        port_file << free_port;
        port_file.close();
    }
    else
    {
        std::cerr << "Error: cannot write to server_port.txt!\n"; 
    }

    close(sock_fd);
    return free_port;
}

// Client-side requests
void Core::Network::network_module::request_handler(int client_socket, const std::string& message)
{
    if (message == "GET_TIME")
    {
        std::string current_time = get_time();
        std::string time_responce = "TIME: " + current_time;
        send_responce(client_socket, time_responce);
    }
    
    else if (message == "GET_STATUS")
    {
        std::string status = get_status();
        std::string status_responce = "SERVER STATUS: " + status;
        
        send_responce(client_socket, status_responce);
    }
}

std::string Core::Network::network_module::get_time()
{
    std::time_t current_time_raw;
    std::time(&current_time_raw);
    
    std::tm* current_time_local = std::localtime(&current_time_raw);
    
    char buffer[9];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", current_time_local);
    
    return std::string(buffer);
}

std::string Core::Network::network_module::get_status()
{
    if (get_current_active_connections() > 0)
    {
        return "The Server is busy";
    }
    else
    {
        return "The Server is Online";
    }
}

void Core::Network::network_module::send_responce(int client_socket, const std::string& responce)
{
    const char* message_responce = responce.c_str();
    size_t message_length = std::strlen(message_responce);

    std::cout << "DEBUG: send_responce() called for client_socket: " << client_socket << ", message: " << responce << ", length: " << message_length << std::endl;

    ssize_t bytes_sent = send(client_socket, message_responce, message_length, 0);

    if (bytes_sent < 0)
    {
        perror("Sending failed!");
        close(client_socket); // Close the client socket on error
        return;
    }
    else if (bytes_sent != message_length)
    {
        std::cerr << "Warning! Sent less bytes than expected, sent: " << bytes_sent << std::endl;
    }
    else
    {
        std::cout << "Successfully sent message to client: " << message_responce << std::endl;
    }
}
