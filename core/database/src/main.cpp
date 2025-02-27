#include <iostream>
#include "database_datamodule.h"

int main()
{
    std::string db_path = "smarthome.db";

    DataModule data_module(db_path);

    if (data_module.createSensorDataTable()) {
        std::cout << "Таблиця sensor_data успішно створена (або вже існувала)." << std::endl;
    } else {
        std::cerr << "Помилка при створенні таблиці sensor_data!" << std::endl;
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

    // **ВСТАВКА ПЕРШИХ ДАНИХ:**
    if (data_module.insertSensorData(timestamp, temperature_value, sensor_type)) {
        std::cout << "Дані датчика температури успішно вставлені в базу даних (перший запис)." << std::endl;
    } else {
        std::cerr << "Помилка при вставці даних датчика температури (перший запис)!" << std::endl;
        return 1;
    }

    // **ВСТАВКА ДРУГИХ ДАНИХ (змінюємо час та температуру):**
    now = std::chrono::system_clock::now() + std::chrono::minutes(1); // Додаємо 1 хвилину до часу
    now_c = std::chrono::system_clock::to_time_t(now);
    localtime_r(&now_c, &now_tm);
    ss.str(""); // Очищаємо stringstream
    ss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");
    timestamp = ss.str();
    temperature_value = 23.7; // Змінюємо температуру

    if (data_module.insertSensorData(timestamp, temperature_value, sensor_type)) {
        std::cout << "Дані датчика температури успішно вставлені в базу даних (другий запис)." << std::endl;
    } else {
        std::cerr << "Помилка при вставці даних датчика температури (другий запис)!" << std::endl;
        return 1;
    }


    // **ОНОВЛЕННЯ ДАНИХ ДЛЯ ID = 2:**
    int id_to_update = 2;
    double new_temperature_value = 25.1; // Нове значення температури
    if (data_module.updateSensorData(id_to_update, new_temperature_value)) {
        std::cout << "Дані з id = " << id_to_update << " успішно оновлені. Нова температура = " << new_temperature_value << std::endl;
    } else {
        std::cerr << "Помилка при оновленні даних з id = " << id_to_update << "!" << std::endl;
        return 1;
    }


    std::cout << "Програма завершила роботу." << std::endl;

    return 0;
}