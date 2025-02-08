cmake_minimum_required(VERSION 3.30)
project(TelecomServer)

set(CMAKE_CXX_STANDARD 20)

# Додаємо шляхи до заголовків
include_directories(include)

# Додаємо вихідні файли
set(SOURCES
    src/main.cpp
    src/core/server.cpp
    src/core/centralnode.cpp
    src/core/station.cpp
    src/core/client.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Створюємо виконуваний файл
add_executable(server ${SOURCES})

# Лінкуємо бібліотеки
target_link_libraries(server pthread)