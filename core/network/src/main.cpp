//
// Created by Mykhailo Khymochko on 27.02.25.
//

#include <network_module.h>
#include <database_datamodule.h>

using namespace std;

int main()
{
    try {
        asio::io_context io_context;

        // **1. Задаємо шлях до бази даних (наприклад, жорстко закодований для тесту)**
        std::string db_path = DATABASE_PATH;

        // **2. Створюємо об'єкт DataModule, передаючи шлях до бази даних в конструктор**
        DataModule data_module(db_path);

        // **3. Отримуємо шлях до бази даних за допомогою геттера getAbsolutePath()**
        std::string db_path_from_getter = data_module.getAbsolutePath();

        // **4. Використовуємо отриманий шлях, наприклад, виводимо на екран (або передаємо в Network Module)**
        std::cout << "Database path from getter: " << db_path_from_getter << std::endl;

        // **5. (Продовження вашого коду) Створення таблиці бази даних (якщо потрібно)**
        if (!data_module.createSensorDataTable()) {
            std::cerr << "Error creating sensor data table. Server cannot start." << std::endl;
            return 1;
        }
        std::cout << "DataModule: Table 'sensor_data' created or already exists (with sensor_type column)." << std::endl;

        // **6. (Продовження вашого коду) Запуск Network Module, передаючи data_module (з ініціалізованою БД)**
        Core::Network::network_module server(data_module);
        server.start();

    } catch (std::exception& e) {
        std::cerr << "Exception in main: " << e.what() << std::endl;
    }

    return 0;
}