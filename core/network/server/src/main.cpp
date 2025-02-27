#include "network_module.h"

int main()
{
    try {
        asio::io_context io_context;

        std::string db_path = "smarthome.db";
        DataModule data_module(db_path);

        if (!data_module.createSensorDataTable()) {
            std::cerr << "Error creating sensor data table. Server cannot start." << std::endl;
            return 1;
        }
        std::cout << "DataModule: Table 'sensor_data' created or already exists (with sensor_type column)." << std::endl;

        Core::Network::network_module server(data_module);
        server.start();

    } catch (std::exception& e) {
        std::cerr << "Exception in main: " << e.what() << std::endl;
    }

    return 0;
}