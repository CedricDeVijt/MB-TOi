cmake_minimum_required(VERSION 3.26)
project(TOi)

set(CMAKE_CXX_STANDARD 23)

add_executable(TOi main.cpp
        CFG.cpp
        PDA.cpp)
