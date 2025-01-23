//
//  BaseStation.cpp
//  ProviderSimulation
//
//  Created by Mykhailo Khymochko on 18.01.2025.
//

#include "../includes/BaseStation.h"
#include <iostream>

BaseStation::BaseStation(int station_id, std::string location, int max_connections, std::vector<Resource> system_resources)
{
    this->station_id = station_id;
    this->max_connections = max_connections;
    this->system_resources = system_resources;
    this->active_connections = 0;
    this->QueueTimeout = 10;
}

void BaseStation::run()
{
    std::thread client_handler([this]
    {
        while(!stop_flag)
        {
            Client client_instance(0, "Unknown", "Standard", 0);
            Client new_client = client_instance.client_system_login(client_instance);

            connect_client(client_instance);

            this->process_request_queue();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    client_handler.detach();
}

void BaseStation::stop()
{
    
}

void BaseStation::process_request_queue()
{
    while (!request_queue.empty())
    {
        // Отримуємо клієнта з найвищим пріоритетом
        Client client = request_queue.top();
        request_queue.pop(); // Видаляємо його з черги

        // Перевіряємо, чи є ресурси для клієнта
        if (active_connections < max_connections)
        {
            Resource allocated = allocate_resources(client);
            if (allocated.available_slots > 0)
            {
                active_connections++;
                std::cout << "Client " << client.getId() << " served successfully.\n";
            }
            else
            {
                std::cout << "Failed to allocate resources for client " << client.getId() << ".\n";
            }
        }
        else
        {
            std::cout << "All resources are busy. Client " << client.getId() << " will wait.\n";
            enqueue_request(client); // Повертаємо назад у чергу
            break;
        }
    }

    if (request_queue.empty())
    {
        std::cout << "Request queue processed. No more clients to serve.\n";
    }
}

void BaseStation::connect_client(Client &client)
{
    if (active_connections < max_connections)
    {
        active_connections++;
        std::vector<Resource> resources = getSystemResources();
        allocate_resources(client);
        setSystemResources(resources);
    }

    else
    {
        std::cout << "Maximum number of connections reached" << std::endl;
        enqueue_request(client);
    }
}

void BaseStation::disconnect_client(Client& client)
{
    if (active_connections > 0)
    {
        active_connections--;
        std::vector<Resource> resources = getSystemResources();
        release_resources(client, resources);
        setSystemResources(resources);
    }

    else
    {
        std::cout << "No active connections to disconnect" << std::endl;
    }
}

Resource BaseStation::allocate_resources(Client& client)
{
    int slots_needed = (client.getPriority() == "VIP") ? 2 : 1; // VIP займає більше

    // Отримуємо ресурси станції
    std::vector<Resource> resources = getSystemResources();

    // Перевіряємо, чи вистачає слотів у першому ресурсі
    if (resources.empty() || resources[0].available_slots < slots_needed)
    {
        std::cout << "Not enough resources for client ID " << client.getId() << std::endl;
        enqueue_request(client); // Додаємо в чергу
        return {}; // Повертаємо пустий ресурс
    }

    // Зменшуємо кількість доступних слотів у ресурсах станції
    resources[0].available_slots -= slots_needed;

    // Оновлюємо виділені слоти для клієнта
    client.setAllocatedSlots(client.getAllocatedSlots() + slots_needed);

    // Оновлюємо ресурси станції
    setSystemResources(resources);

    // Лог
    std::cout << "Client ID " << client.getId()
              << " (" << client.getPriority() << ") allocated "
              << slots_needed << " slots. Available slots: "
              << resources[0].available_slots << std::endl;

    // Повертаємо оновлений ресурс
    return resources[0];
}

void BaseStation::release_resources(Client &client, std::vector<Resource>& resources)
{
    int slots_needed = client.getAllocatedSlots();

    if (slots_needed > 0)
    {
        for (int i = 0; i < resources.size(); i++)
        {
            int slots_to_free = std::min(slots_needed, resources[i].total_slots - resources[i].available_slots); // Максимум 2 слоти
            resources[i].available_slots += slots_to_free;
            slots_needed -= slots_to_free;

            if (slots_needed == 0)
            {
                break;
            }
        }
    }
    
    else
    {
        std::cout << "Client " << client.getId() << " has no allocated slots" << std::endl;
    }
}

void BaseStation::enqueue_request(Client& client)
{
    if (client.getId() == -1)
    {
        client.setId(generate_id());
    }

    if (client.getLocation().empty() || client.getPriority().empty())
    {
        client = client.client_system_login(client);
    }

    request_queue.push(client);

    std::cout << "Client with ID " << client.getId()
            << " added to the queue. Priority: " << client.getPriority()
            << ", Location: " << client.getLocation()
            << ". Current queue size: " << request_queue.size() << std::endl;
}

void BaseStation::dequeue_request()
{
    
}

void Show()
{

}
