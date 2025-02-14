cmake_minimum_required(VERSION 3.30)
project(Server)

set(CMAKE_CXX_STANDARD 20)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/main.cpp
    src/core/server.cpp
    src/core/node.cpp
    src/core/client.cpp
)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create executable
add_executable(server ${SOURCES})

# Link libraries
target_link_libraries(server pthread)