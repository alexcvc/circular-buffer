# Set project name
set(TargetName circular_buffer_example)

add_executable( ${TargetName} main.cpp)
target_include_directories( ${TargetName} PRIVATE ../include )
