#pragma once

#include "BaseStation.h"
#include "../includes/Client.h"

#include <iostream>
#include <map>

class CentralNode
{
private:

    std::string default_location_list[4] = {"Kyiv", "Berlin", "New York", "Tokyo"};

    std::vector<std::string> new_location_list;

    std::map<int, BaseStation> stations_list;

public:

    CentralNode() : stations_list{} {};
    ~CentralNode();

    std::string select_location(std::string default_location_list[]);

    void client_to_station(Client &client, std::map<int, BaseStation> stations_list);

    //Getters
    BaseStation& getStation(int id) 
    {
        if (stations_list.find(id) == stations_list.end())
        {
            throw std::runtime_error("Station ID was not found!");
        }

        return stations_list[id];
    }

    std::string get_location() const {
    
    }

    size_t getStationListSize() const { return stations_list.size(); }

    //Setters
    void setStation(int id, const BaseStation& station) 
    {
        stations_list.emplace(id, station);
    }

    int generate_station_id();

    void show_station_list();
};