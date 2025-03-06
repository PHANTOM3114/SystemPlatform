cmake_minimum_required(VERSION 3.30)
project(database) # Зміни назву проєкту, щоб не плутатися

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(database src/main.cpp
        src/core/database_datamodule.cpp
        include/database_datamodule.h) # Зміни назву цілі

# **SQLite3 C library linking - дуже просто!**
target_link_libraries(database PRIVATE sqlite3) # Лінкуємо з системною бібліотекою sqlite3