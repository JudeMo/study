cmake_minimum_required(VERSION 3.3)
project(struct)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
#    polynomial.c
    polynomial.cpp)

add_executable(struct ${SOURCE_FILES})