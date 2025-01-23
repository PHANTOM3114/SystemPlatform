//
//  Client.cpp
//  ProviderSimulation
//
//  Created by Mykhailo Khymochko on 18.01.2025.
//

#include "../includes/Client.h"

Client::Client(int id, std::string location, std::string priority, int allocated_slots) : id(id), location(location), priority(priority), allocated_slots(allocated_slots)
{
    this->id = id;
    this->location = location;
    this->priority = priority;
    this->allocated_slots = allocated_slots;
};

Client::~Client() = default;

Client Client::client_system_login(Client &client)
{
    std::string client_location;
    std::string client_priority;

    std::cout << "Authentificate in the system, please!" << std::endl;

    do {
        std::cout << "Enter your location, and priority(VIP or Standart): ";
        std::cin >> client_location >> client_priority;

        client.setLocation(client_location);
        client.setPriority(client_priority);

        // Перевірка priority
        if (client_priority != "VIP" && client_priority != "Standart") {
            std::cout << "Invalid priority. Please enter 'VIP' or 'Standart'." << std::endl;
        }
    } while (client_priority != "VIP" && client_priority != "Standart");

    return client;
    
}


int generate_client_id()
{
    return rand() % 100000;
}
