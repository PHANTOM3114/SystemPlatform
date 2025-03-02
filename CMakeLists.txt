cmake_minimum_required(VERSION 3.30)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0 # <---- АБО ОСТАННЮ ВЕРСІЮ З https://github.com/google/googletest/releases
)

FetchContent_MakeAvailable(googletest)

project(SystemPlatform) # <---- КОМАНДА project() ТЕПЕР ПІСЛЯ FetchContent!!!

set(CMAKE_CXX_STANDARD 20)

set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests) # <----  ВИПРАВТЕ ДРУКАРСЬКУ ПОМИЛКУ: CMAKE_SOURCE/DIR -> CMAKE_SOURCE_DIR

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/core/include
    # ${CMAKE_SOURCE_DIR}/core/network/include
    ${CMAKE_SOURCE_DIR}/core/network/server/include
    # Додайте інші include директорії, якщо потрібно
)

# Додаємо піддиректорії з CMakeLists.txt для сервера, клієнта та тестів
add_subdirectory(core/network/server)
add_subdirectory(core/network/client)
add_subdirectory(${TESTS_DIR}) # <----  ${TESTS_DIR} ТЕПЕР ПОВИНЕН БУТИ ВИЗНАЧЕНИЙ ПРАВИЛЬНО

# **ВАЖЛИВО: В КОРЕНЕВОМУ CMakeLists.txt НЕМАЄ РЯДКІВ target_link_libraries ДЛЯ GTEST!!!**
# **ЛІНКУВАННЯ З GTEST БУДЕ В ФАЙЛІ tests/CMakeLists.txt**
