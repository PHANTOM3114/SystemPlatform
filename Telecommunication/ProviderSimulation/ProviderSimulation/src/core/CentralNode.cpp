#include "../includes/CentralNode.h"

CentralNode::CentralNode()
{
    for (int i = 0; i < 4; i++)
    {
        int unique_station_id = CentralNode::generate_station_id();
        std::string unique_location = select_location(default_location_list);

        stations_list.emplace(std::make_pair(unique_station_id, BaseStation(unique_station_id, unique_location, 10, {})));
    }
    
}

std::string CentralNode::select_location(std::string default_location_list[])
{
    if (default_location_list == nullptr || default_location_list[0].empty())
    {
        throw std::runtime_error("Default location list is empty");
    }

    if (new_location_list.empty())
    {
        throw std::runtime_error("No locations available!");
    }

    std::string location = default_location_list[0];
    new_location_list.erase(new_location_list.begin());
    
    return location;
}

void CentralNode::client_to_station(Client &client, std::map<int, BaseStation> stations_list)
{
    for (int i = 0; i < stations_list.size(); i++)
    {

    }
}

int CentralNode::generate_station_id()
{
    return rand() % 100000;
}

//Тимчасовий метод
void CentralNode::show_station_list()
{
    for (const auto& [id, station] : stations_list) {
    std::cout << "Station ID: " << id 
              << "\n";
}
}
    
