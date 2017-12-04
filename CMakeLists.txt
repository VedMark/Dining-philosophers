cmake_minimum_required(VERSION 3.5)
project(dining_philosophers)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(dining_philosophers main.cpp philosopher.cpp philosopher.h fork.cpp fork.h)
target_link_libraries(dining_philosophers rt)