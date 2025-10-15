cmake_minimum_required(VERSION 3.14)
project(CPOM_Project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(NumberLib Numb.cpp)
target_include_directories(NumberLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(run_custom_tests test_runner.cpp tests.cpp)

target_link_libraries(run_custom_tests PRIVATE NumberLib)