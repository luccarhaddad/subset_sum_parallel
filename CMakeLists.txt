cmake_minimum_required(VERSION 3.28)
project(Lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab3 main.cpp
        utils/solver.cpp
        utils/solver.h
        utils/test.cpp
        utils/test.h)
