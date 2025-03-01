cmake_minimum_required(VERSION 3.30)

project(network_module)

find_package(asio CONFIG REQUIRED) # <---- ДОДАНО find_package ДЛЯ asio!
find_package(nlohmann_json REQUIRED) # <---- find_package ДЛЯ nlohmann_json ВЖЕ БУВ, ЛИШАЄМО!

set(HEADER_FILES
        include/network_module.h
)

set(SOURCE_FILES
        src/core/network_module.cpp
        src/main.cpp #  Можливо, цей main.cpp тут зайвий, якщо він не використовується для збірки бібліотеки
)

include_directories(
        include
)

add_library(network_module STATIC
        ${HEADER_FILES}
        ${SOURCE_FILES}
)

target_link_libraries(network_module
        PRIVATE
        asio::asio # <---- ЛІНКУЄМОСЯ З asio через TARGET_LINK_LIBRARIES!
        nlohmann_json::nlohmann_json # <---- ЛІНКУЄМОСЯ З nlohmann_json через TARGET_LINK_LIBRARIES!
        pthread
        datamanagement_module # ЛІНКУЄМОСЯ З datamanagement_module - ЦЕ ВАЖЛИВО!
)

target_include_directories(network_module
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)