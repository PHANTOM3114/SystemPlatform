cmake_minimum_required(VERSION 3.30)

# Set the project name
project(SecurityModule)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(SecurityModule src/main.cpp)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Link libraries (if any)
# target_link_libraries(SecurityModule <library_name>)