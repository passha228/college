cmake_minimum_required(VERSION 3.19)
project(file_sort)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(file_sort
        file_function.cpp
        Header.h
        Heap_sort.h
        main.cpp)
