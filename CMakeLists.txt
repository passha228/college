cmake_minimum_required(VERSION 3.19)
project(Haffman)


include_directories(include)
set(CMAKE_CXX_STANDARD 20)


add_executable(Haffman

        main.cpp
        Btree.cpp
        Node.cpp
        )