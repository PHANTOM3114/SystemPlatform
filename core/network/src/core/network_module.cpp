//
// Created by Mykhailo Khymochko on 27.02.25.
//

#include <network_module.h>
#include <database_datamodule.h>
#include <sstream> // Required for ostringstream

Core::Network::network_module::network_module(DataModule& dataModule) : data_module(dataModule)
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

void Core::Network::network_module::start() {
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

void* Core::Network::network_module::handle_client(int client_socket)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1); // Змінено: читаємо ОДИН раз

    if (bytes_read > 0) // Перевіряємо, чи прочитано дані
    {
        buffer[bytes_read] = '\0';
        std::string message(buffer);
        std::cout << "Server received raw message: " << message << std::endl; // Логуємо сире повідомлення

        try
        {
            nlohmann::json json_message = nlohmann::json::parse(message);
            std::cout << "Server parsed JSON: " << json_message.dump() << std::endl; // Логуємо розпарсений JSON

            std::string timestamp = json_message["timestamp"];
            std::string sensor_type = json_message["sensor_type"];
            double temperature  = json_message["temperature"].get<double>();

            std::cout << "Extracted data: timestamp = " << timestamp << ", sensor_type = " << sensor_type << ", temperature = " << temperature << std::endl; // Логуємо витягнуті дані

            if (this->data_module.insertSensorData(timestamp, temperature, sensor_type))
            {
                std::cout << "Data inserted successfully from JSON message." << std::endl;
                const char* response = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"status\": \"success\", \"message\": \"Data inserted\"}"; // JSON response with Content-Type
                send(client_socket, response, strlen(response), 0);
            }
            else
            {
                std::cerr << "Error inserting data from JSON message!" << std::endl;
                const char* response = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"status\": \"error\", \"message\": \"Database insertion failed\"}"; // JSON error response with Content-Type
                send(client_socket, response, strlen(response), 0);
            }
        }
        catch (nlohmann::json::parse_error& e)
        {
            std::cerr << "JSON parse error: " << e.what() << " in message: " << message << std::endl;
            std::string error_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"status\": \"error\", \"message\": \"Invalid JSON format\", \"details\": \"" + std::string(e.what()) + "\"}";
            send(client_socket, error_response.c_str(), error_response.length(), 0);
        }
        catch (std::exception& e)
        {
            std::cerr << "Exception while processing JSON message: " << e.what() << std::endl;
            std::string error_response = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/json\r\n\r\n{\"status\": \"error\", \"message\": \"Server error\", \"details\": \"" + std::string(e.what()) + "\"}";
            send(client_socket, error_response.c_str(), error_response.length(), 0);
        }
    }
    else if (bytes_read == 0)
    {
        std::cout << "Client disconnected gracefully." << std::endl; // Handle graceful disconnection
    }
    else
    {
        perror("Error reading from client"); // Handle read error
    }

    std::cout << "Client has disconnected\n"; // Лог після обробки і відправки відповіді
    close(client_socket);
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

    std::filesystem::path basePath = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path();
    std::filesystem::path absolute = basePath / "data/server_port.txt";

    std::cout << "Trying to open file at: " << absolute << std::endl;

    std::ofstream port_file(absolute, std::ios::trunc);

    if (!std::filesystem::exists(absolute)) {
        std::cerr << "File does not exist! Trying to create..." << std::endl;
        std::ofstream create_file(absolute);
        if (!create_file) {
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