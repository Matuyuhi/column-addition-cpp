cmake_minimum_required(VERSION 3.22.1)
project(work)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(work src/main.cpp
        header/BigInt.h
        src/BigInt.cpp)
