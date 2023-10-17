cmake_minimum_required(VERSION 3.22.1)
project(work)

set(CMAKE_CXX_STANDARD 20)

add_executable(work src/main.cpp
        header/Evaluator.h
        src/Evaluator.cpp)
