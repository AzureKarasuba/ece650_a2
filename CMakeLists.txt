cmake_minimum_required(VERSION 3.24)
project(ece650_a2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ece650_a2
        main.cpp
        Vertex.cpp
        Vertex.h)
