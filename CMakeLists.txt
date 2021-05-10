cmake_minimum_required(VERSION 3.19)
project(class_tree)
set(CMAKE_CXX_STANDARD 20)

find_package(FreeGLUT)


include_directories(include)


add_executable(Class_tree

        Btree.cpp
        test.cpp
        STree.cpp

        )
target_link_libraries(Class_tree ${FreeGLUT_LIBRARIES})