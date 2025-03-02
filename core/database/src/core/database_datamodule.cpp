//
// Created by Mykhailo Khymochko on 26.02.25.
//

#include "database_datamodule.h"

DataModule::DataModule(const std::string &db_path) : db_connection_(nullptr)
{
    int rc = sqlite3_open(db_path.c_str(), &db_connection_);

    if (rc != SQLITE_OK)
    {
        std::cerr << "Can't open database!" << std::endl;
        sqlite3_close(db_connection_);
        db_connection_ = nullptr;
    }
    else
    {
        std::cout << "DataModule: Database opening is successful: " << db_path << std::endl;
    }
}

DataModule::~DataModule()
{
    if (db_connection_)
    {
        sqlite3_close(db_connection_);
        std::cout << "DataModule: Connection was closed successfully" << std::endl;
    }
}

bool DataModule::createSensorDataTable() {
    if (!db_connection_) {
        std::cerr << "Error: Database connection is not established." << std::endl;
        return false;
    }

    const char* sql_create_table =
        "CREATE TABLE IF NOT EXISTS sensor_data ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    timestamp TEXT NOT NULL,"
        "    temperature REAL NOT NULL,"
        "    sensor_type TEXT NOT NULL"
        ");";

    char* errMsg = 0;
    int rc = sqlite3_exec(db_connection_, sql_create_table, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    } else {
        std::cout << "DataModule: Table 'sensor_data' created or already exists (with sensor_type column)." << std::endl;
        return true;
    }
}

bool DataModule::insertSensorData(const std::string& timestamp, double temperature, const std::string& sensor_type)
{
    if (!db_connection_)
    {
        std::cerr << "Error: Database connection is not established." << std::endl;
        return false;
    }

    const char* sql_insert_data = "INSERT INTO sensor_data (timestamp, temperature, sensor_type) VALUES (?, ?, ?);";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_connection_, sql_insert_data, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) // **ДОДАНО ПЕРЕВІРКУ РЕЗУЛЬТАТУ sqlite3_prepare_v2()!**
    {
        std::cerr << "SQL prepare error: code = " << rc << ", message: " << sqlite3_errmsg(db_connection_) << std::endl; // **Виводимо код помилки і повідомлення для sqlite3_prepare_v2()**
        return false; // Якщо підготовка не вдалася - виходимо з помилкою
    }

    int paramIndexTimestamp = 1;
    int paramIndexTemperature = 2;
    int paramIndexSensorType = 3;

    sqlite3_bind_text(stmt, paramIndexTimestamp, timestamp.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, paramIndexTemperature, temperature);
    sqlite3_bind_text(stmt, paramIndexSensorType, sensor_type.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE)
    {
        std::cerr << "SQL step error code: " << rc << ", error message: " << sqlite3_errmsg(db_connection_) << std::endl; // **Залишаємо вивід коду помилки для sqlite_step()**
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);

    std::cout << "DataModule: Before main output - temperature value is: " << temperature << std::endl;

    std::cout << "DataModule: Data inserted successfully: timestamp=" << timestamp
              << ", sensor_type=" << sensor_type
              << ", temperature=" << std::to_string(temperature)
              << std::endl;

    return true;
}