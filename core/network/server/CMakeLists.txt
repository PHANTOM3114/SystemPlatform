cmake_minimum_required(VERSION 3.30)
project(Server) # **Залишаємо project(Server), це назва ПІДПРОЄКТУ**

set(CMAKE_CXX_STANDARD 20) # **Залишаємо стандарт C++ - він може бути різним для різних підпроєктів, але тут він однаковий**

# Include directories - **ЗМІНЮЄМО ШЛЯХИ, щоб були відносно кореня проєкту**
include_directories(${CMAKE_SOURCE_DIR}/include) # **${CMAKE_SOURCE_DIR} вказує на КОРІНЬ ПРОЄКТУ SystemPlatform тепер!**

# Add source files - **ШЛЯХИ ВЖЕ ПРАВИЛЬНІ, бо вони відносні до папки server**
set(SOURCES
    src/main.cpp
    src/core/network_module.cpp
)

# Set the output directory - **ЗАЛИШАЄМО ЯК Є, але тепер відносно build папки в корені SystemPlatform**
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # **${CMAKE_BINARY_DIR} тепер - це папка build в корені SystemPlatform!**

# Create executable - **НАЗВА ВИКОНУВАНОГО ФАЙЛУ "server" ЗАЛИШАЄТЬСЯ**
add_executable(server ${SOURCES})

# Link libraries - **ЗАЛИШАЄМО ЯК Є**
target_link_libraries(server pthread)