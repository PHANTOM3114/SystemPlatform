cmake_minimum_required(VERSION 3.30)
project(SystemPlatform)

set(CMAKE_CXX_STANDARD 20)

set(DATABASE_ROOT_DIR "${CMAKE_BINARY_DIR}") # <---- ЗМІНЕНО НА CMAKE_BINARY_DIR!
set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(CORE_DIR ${CMAKE_SOURCE_DIR}/core)
set(DATABASE_DIR ${CMAKE_SOURCE_DIR}/databases)
set(DATA_STORAGE_MODULE_DIR ${CORE_DIR}/datamanagement) # <---- ЗВЕРНИ УВАГУ, ПАПКА ТЕПЕР "datamanagement", А НЕ "modules/data_storage"!
set(NETWORK_MODULE_DIR ${CORE_DIR}/network)          # <---- ПАПКА "network", А НЕ "modules/network"!
set(CONFIG_DIR ${CMAKE_SOURCE_DIR}/cmake)

include_directories(
        ${INCLUDE_DIR}
        ${CORE_DIR}/include
        ${DATA_STORAGE_MODULE_DIR}/include # <---- Шлях до include папки data_management (виправлено назву модуля!)
        ${NETWORK_MODULE_DIR}/include      # <---- Шлях до include папки network
        ${CONFIG_DIR} #  Для config.h.in
        # ${DATABASE_DIR} #  Зазвичай databases не треба в include_directories
        ${CMAKE_BINARY_DIR} #  Для згенерованого config.h
)

add_subdirectory(${TESTS_DIR})
add_subdirectory(${DATA_STORAGE_MODULE_DIR}) # <---- Підпроєкт data_management (виправлено назву модуля!)
add_subdirectory(${NETWORK_MODULE_DIR})      # <---- Підпроєкт network

configure_file(cmake/config.h.in ${CMAKE_BINARY_DIR}/config.h)

# ЯВНО ПЕРЕЛІЧУЄМО .cpp ФАЙЛИ ДЛЯ SystemPlatform!
set(SYSTEMPLATFORM_SOURCES
        core/src/main.cpp # <---- Припускаємо, main.cpp в корені проєкту
        core/src/main.cpp # <---- Якщо є main.cpp в core/src
        core/network/src/main.cpp # <---- main.cpp для network
        core/datamanagement/src/main.cpp # <---- main.cpp для datamanagement (хоча це дивно)
        ${DATA_STORAGE_MODULE_DIR}/src/core/database_datamodule.cpp # <---- database_datamodule.cpp з datamanagement
        ${NETWORK_MODULE_DIR}/src/core/network_module.cpp          # <---- network_module.cpp з network
        # ... ДОДАЙ СЮДИ ШЛЯХИ ДО ІНШИХ .cpp ФАЙЛІВ, ЯКЩО ТРЕБА, ЯКІ МАЮТЬ БУТИ В SystemPlatform ...
)


add_executable(SystemPlatform
        ${SYSTEMPLATFORM_SOURCES} # <---- ВИКОРИСТОВУЄМО ЗМІННУ зі СПИСКОМ .cpp ФАЙЛІВ!
)

find_package(nlohmann_json REQUIRED)

target_link_libraries(SystemPlatform
        PRIVATE
        pthread
        sqlite3
        nlohmann_json::nlohmann_json
        datamanagement_module # <---- ЛІНКУЄМОСЯ З БІБЛІОТЕКОЮ data_management (виправлено назву модуля!)
        network_module      # <---- ЛІНКУЄМОСЯ З БІБЛІОТЕКОЮ network_module
)