cmake_minimum_required(VERSION 3.30)
project(SystemPlatformTests)

enable_testing()

find_package(GTest CONFIG REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/core/include
    ${CMAKE_SOURCE_DIR}/core/network/server/include
)

# Add the network_module library target
add_library(network_module STATIC
    ${CMAKE_SOURCE_DIR}/core/network/server/src/core/network_module.cpp
)

set(TEST_SOURCES
    network_module_test.cpp
)

add_executable(system_platform_tests ${TEST_SOURCES})

target_link_libraries(system_platform_tests PRIVATE
    GTest::gtest_main
    GTest::gtest
    network_module
)

add_test(NAME SystemPlatformUnitTests COMMAND system_platform_tests)
