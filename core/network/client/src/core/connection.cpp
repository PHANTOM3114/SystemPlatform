#include "connection.h"

Connection::Connection(int port) {
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Error creating socket!");
        exit(EXIT_FAILURE);
    }

    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socket_addr.sin_port = htons(port);
}

Connection::~Connection() {
    close(sock_fd);
}

void Connection::connect_to_server() {
    if (connect(sock_fd, (struct sockaddr*)&socket_addr, sizeof(socket_addr)) < 0) {
        perror("Connection failed!");
        exit(EXIT_FAILURE);
    }
    std::cout << "Connecting was successful!" << std::endl;
}

void Connection::send_message()
{
    int user_choice = 0;
    std::string user_message;
    
    while (true)
    {
        std::cout << "Enter 1 for sending a message, or 2 for exit: ";
        std::cin >> user_choice;
        
        if (std::cin.fail())
        {
            std::cout << "Invalid option has chosen!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else if (user_choice == 1)
        {
            std::cout << "Enter a message: " << std::endl;
            std::cin.ignore();
            std::getline(std::cin, user_message);
            
            send_user_message(user_message);
            
        }
        else if (user_choice == 2)
        {
            send_wave_hand();
            break;
        }
        else if(user_choice == 3)
        {
            std::cout << "Exiting message sending \n";
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
        
        std::cout << "Back to main menu (or wherever you want to go after sending messages).\n";
    }
    
   

}

void Connection::send_user_message(const std::string& message)
{
    if (send(sock_fd, message.c_str(), message.size(), 0))
    {
        std::cout << "Message sent: " << message << std::endl;
        std::cout << "Message was sent successfully!" << std::endl;
    }
}

void Connection::send_wave_hand()
{
    std::string wave_message = "wave"; // **Визначаємо повідомлення для "wave a hand"**
    send(sock_fd, wave_message.c_str(), wave_message.size(), 0);
    std::cout << "Wave hand signal sent!\n";
}
