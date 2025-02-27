cmake_minimum_required(VERSION 3.30)
project(server)

set(CMAKE_CXX_STANDARD 20)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../../database/include)

# Add source files
set(SOURCES
        src/main.cpp
        src/core/network_module.cpp
        ../../database/src/core/database_datamodule.cpp
)

find_package(nlohmann_json 3.11.3 REQUIRED)
find_package(SQLite3 REQUIRED)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create executable
add_executable(server ${SOURCES})

# Link libraries
target_link_libraries(server PRIVATE pthread sqlite3 nlohmann_json::nlohmann_json)

