cmake_minimum_required(VERSION 3.5)
project(CSE340P5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES compiler.c compiler.h compile.c)
add_executable(CSE340P5 ${SOURCE_FILES})