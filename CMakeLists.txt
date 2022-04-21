cmake_minimum_required(VERSION 3.18.4)
project(algorithm)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
#add_executable(tests tests.cpp)
#target_link_libraries(tests GTest::gtest_main)
