cmake_minimum_required(VERSION 3.30)

# Set the project name - **ЗАЛИШАЄМО project(Client), це назва ПІДПРОЄКТУ**
project(client)

# Specify the C++ standard - **ЗАЛИШАЄМО ЯК Є**
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Add the executable - **ШЛЯХИ ДО ФАЙЛІВ ВЖЕ ПРАВИЛЬНІ, бо відносні до папки client**
add_executable(Client src/main.cpp
    src/core/client.cpp
    src/core/connection.cpp
)

# Include directories - **ЗМІНЮЄМО ШЛЯХИ, щоб були відносно кореня проєкту**
include_directories(${PROJECT_SOURCE_DIR}/include) # **${PROJECT_SOURCE_DIR} тут також вказує на КОРІНЬ ПРОЄКТУ SystemPlatform!**

# Link libraries (if any) - **ЗАЛИШАЄМО ЯК Є**
# target_link_libraries(NetworkClient <library_name>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..) # **ЗАЛИШАЄМО ЯК Є, але тепер відносно build папки в корені SystemPlatform**
# Add other source files
# set(SOURCES src/file1.cpp src/file2.cpp)
# add_executable(NetworkClient ${SOURCES})
