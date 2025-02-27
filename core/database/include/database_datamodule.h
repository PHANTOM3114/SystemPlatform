//
// Created by Mykhailo Khymochko on 26.02.25.
//

#ifndef DATABASE_DATAMODULE_H
#define DATABASE_DATAMODULE_H

#include <sqlite3.h>
#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>

class DataModule
{
private:
    sqlite3* db_connection_;

public:

    DataModule(const std::string& db_path);
    ~DataModule();

    bool createSensorDataTable();
    bool insertSensorData(const std::string& timestamp, double temperature, const std::string& sensor_type);
    bool deleteSensorData(int id);
    bool updateSensorData(int id, double new_temperature);
};

#endif //DATABASE_DATAMODULE_H
