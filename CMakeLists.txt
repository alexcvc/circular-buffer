cmake_minimum_required(VERSION 3.27)
project(CircularBuffer)

add_executable(CircularBuffer main.cpp include/CircularBuffer.h )
target_include_directories(CircularBuffer PUBLIC include)

add_subdirectory(examples)
add_subdirectory(test)
