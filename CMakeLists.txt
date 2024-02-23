cmake_minimum_required(VERSION 3.27)
project(CircularBuffer)

set(CMAKE_CXX_STANDARD 98)

add_executable(CircularBuffer main.cpp include/CircularBuffer.h )
target_include_directories(CircularBuffer PUBLIC include)

add_subdirectory(examples)
add_subdirectory(test)
