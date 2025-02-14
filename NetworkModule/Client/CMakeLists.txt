cmake_minimum_required(VERSION 3.30)

# Set the project name
project(NetworkClient)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(NetworkClient src/main.cpp)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Link libraries (if any)
# target_link_libraries(NetworkClient <library_name>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
# Add other source files
# set(SOURCES src/file1.cpp src/file2.cpp)
# add_executable(NetworkClient ${SOURCES})