#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <atomic>
#include "../includes/Client.h"

struct Resource {
    int total_slots;
    int available_slots;
};

class BaseStation
{
private:
    
    std::string location;
    int station_id;

    int max_connections;
    std::atomic<int> active_connections;

    std::vector<Resource> system_resources;
    std::priority_queue<Client, std::vector<Client>, PriorityComparator> request_queue;    
    int QueueTimeout;

    std::vector<std::thread> worker_threads;
    std::atomic <bool> stop_flag;
  
    int generate_id();

public:
    BaseStation(int station_id, std::string location, int max_connections, std::vector<Resource> system_resources);
    ~BaseStation();

    //Program Control Methods
    void run();
    void stop();

    //Client working methods
    void process_request_queue();
    void connect_client(Client& client);
    void disconnect_client(Client& client);

    //Station resources
    Resource allocate_resources(Client& client);
    void release_resources(Client& client, std::vector<Resource>& resources);
    void show();

    //Clients queue
    void enqueue_request(Client& client);
    void dequeue_request();

    //Monitoring and logging
    BaseStation get_status();
    void log_event();

    //Getters
    std::string getLocation() const { return location; }
    std::vector<Resource> getSystemResources() const { return system_resources; }

    // Setters
    void setLocation(const std::string& loc) { location = loc; }
    void setSystemResources(const std::vector<Resource>& res) { system_resources = res; }
};

