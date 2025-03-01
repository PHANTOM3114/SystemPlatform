//
// Created by Mykhailo Khymochko on 27.02.25.
//

#include <database_datamodule.h>

DataModule::DataModule(const std::string& db_path) : db_connection_(nullptr)
{
    absolute_path_ = std::filesystem::absolute(db_path);
    int rc = sqlite3_open(absolute_path_.string().c_str(), &db_connection_);

    if (rc) {
        std::cerr << "DataModule: Cannot open database: " << sqlite3_errmsg(db_connection_) << std::endl;
        return;
    } else {
        std::cout << "DataModule: Database opening is successful: " << absolute_path_.string() << std::endl;
    }
}


DataModule::~DataModule()
{
    if (db_connection_) {
        sqlite3_close(db_connection_);
        std::cout << "DataModule: Connection was closed successfully" << std::endl;
    }
}

bool DataModule::createSensorDataTable() {
    const char *sqlCreateTable = "CREATE TABLE IF NOT EXISTS sensor_data ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "timestamp TEXT NOT NULL,"
                                 "temperature REAL,"
                                 "sensor_type TEXT NOT NULL" // Додано колонку sensor_type
                                 ");";
    char *errMsg = 0;
    int rc = sqlite3_exec(db_connection_, sqlCreateTable, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "DataModule: Can't create table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
     std::cout << "DataModule: Table 'sensor_data' created or already exists (with sensor_type column)." << std::endl;
    return true;
}


bool DataModule::insertSensorData(const std::string& timestamp, double temperature, const std::string& sensor_type) {
    std::string sqlInsert = "INSERT INTO sensor_data (timestamp, temperature, sensor_type) VALUES ('" + timestamp + "', " + std::to_string(temperature) + ", '" + sensor_type + "');";
    char *errMsg = 0;
    int rc = sqlite3_exec(db_connection_, sqlInsert.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "DataModule: Can't insert data: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    std::cout << "DataModule: Data inserted successfully: timestamp=" << timestamp << ", sensor_type=" << sensor_type << ", temperature=" << temperature << std::endl;
    return true;
}

bool DataModule::deleteSensorData(int id) {
    std::string sqlDelete = "DELETE FROM sensor_data WHERE id = " + std::to_string(id) + ";";
    char *errMsg = 0;
    int rc = sqlite3_exec(db_connection_, sqlDelete.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "DataModule: Can't delete data: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    std::cout << "DataModule: Data deleted successfully: id=" << id << std::endl;
    return true;
}

bool DataModule::updateSensorData(int id, double new_temperature) {
    std::string sqlUpdate = "UPDATE sensor_data SET temperature = " + std::to_string(new_temperature) + " WHERE id = " + std::to_string(id) + ";";
    char *errMsg = 0;
    int rc = sqlite3_exec(db_connection_, sqlUpdate.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "DataModule: Can't update data: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    std::cout << "DataModule: Data updated successfully: id=" << id << ", new_temperature=" << new_temperature << std::endl;
    return true;
}