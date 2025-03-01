cmake_minimum_required(VERSION 3.30) # Мінімальна версія CMake

project(datamanagement_module) # <---- НАЗВА ПРОЄКТУ МОДУЛЯ - ВАЖЛИВО!

find_package(SQLite3 REQUIRED) # <---- ДОДАНО find_package ДЛЯ SQLite3!

set(HEADER_FILES
        include/database_datamodule.h # Шлях до хедер файлу відносно папки CMakeLists.txt
)

set(SOURCE_FILES
        src/core/database_datamodule.cpp # Шлях до cpp файлу відносно папки CMakeLists.txt
        src/main.cpp                    # Шлях до main.cpp (якщо він потрібен для модуля, хоча тут дивно його бачити)
)

include_directories(
        include # Вказуємо, що include папка модуля є папкою з хедерами
)

add_library(datamanagement_module STATIC # <---- Створюємо СТАТИЧНУ бібліотеку з назвою datamanagement_module - ВАЖЛИВО!
        ${HEADER_FILES} # Хедер файли модуля
        ${SOURCE_FILES} # Source файли модуля
)

target_link_libraries(datamanagement_module # Лінкуємо бібліотеку datamanagement_module
        PRIVATE
        sqlite3 # З бібліотекою sqlite3, яка потрібна для цього модуля
)

target_include_directories(datamanagement_module # Вказуємо include директорії для бібліотеки
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # PUBLIC include директорія для INTERFACE і BUILD_INTERFACE
        $<INSTALL_INTERFACE:include> # PUBLIC include директорія для INSTALL_INTERFACE
)