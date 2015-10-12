cmake_minimum_required(VERSION 3.3)
project(struct)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_VERBOSE_MAKEFILE on)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(C_polynomial polynomial.c)
set(CPP_polynomial polynomial.cpp)
set(C_isomorphism isomorphism.c)
set(C_reversingLink reversingLink.c)
set(C_subsequence subsequence.cpp)

add_executable(C_polynomial ${C_polynomial})
add_executable(CPP_polynomial ${CPP_polynomial})
add_executable(C_isomorphism ${C_isomorphism})
add_executable(C_reversingLink ${C_reversingLink})
add_executable(C_subsequence ${C_subsequence})