#include <iostream>
#include "database_datamodule.h"

int main()
{
    std::string db_path = "smarthome.db";

    DataModule data_module(db_path);

    if (data_module.createSensorDataTable())
    {
        std::cout << "Table sensor_data was set up successfully (or it have existed yet)." << std::endl;
    }
    else
    {
        std::cerr << "Error creating sensor_data table!" << std::endl;
        return 1;
    }

    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    std::tm now_tm;
    localtime_r(&now_c, &now_tm);
    std::stringstream ss;

    ss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = ss.str();

    double temperature_value = 22.5;
    std::string sensor_type = "temperature_sensor"; 

    if (data_module.insertSensorData(timestamp, temperature_value, sensor_type))
    {
        std::cout << "Temperature sensor data was set successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Setting up temperature sensor data error!" << std::endl;
        return 1;
    }


    std::cout << "Програма завершила роботу." << std::endl;

    return 0;
}