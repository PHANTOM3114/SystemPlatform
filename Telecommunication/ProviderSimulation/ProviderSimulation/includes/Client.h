//
//  Client.h
//  ProviderSimulation
//
//  Created by Mykhailo Khymochko on 18.01.2025.
//

#pragma once

#include "../includes/BaseStation.h"
#include <iostream>

class Client
{
private:

    int id;
    int allocated_slots;
    int available_slots;

    std::string location;
    std::string priority;

public:
    Client(int id, std::string location, std::string priority, int allocated_slots);
    ~Client();

    Client client_system_login(Client &client);

    //Getters
    int getId() const { return id; }
    std::string getLocation() const { return location; }
    std::string getPriority() const { return priority; }
    int getAllocatedSlots() const { return allocated_slots; }
    int getAvailableSlots() const { return available_slots; }
    

    //Setters
    void setId(int id) { this->id = id; }
    void setLocation(std::string location) { this->location = location; }
    void setPriority(std::string priority) { this->priority = priority; }
    void setAllocatedSlots(int allocated_slots) { this->allocated_slots = allocated_slots; }
    void setAvailableSlots(int available_slots) { this->available_slots = available_slots; }

    int generate_id();

};

struct PriorityComparator
{
    bool operator()(const Client& client_1, const Client& client_2) const
    {
        if (client_1.getPriority() == "VIP" && client_2.getPriority() == "Standart")
        {
            return false;
        }

        if (client_1.getPriority() == "Standart" && client_2.getPriority() == "VIP")
        {
            return true;
        }
        return client_1.getId() > client_2.getId();
    }
};