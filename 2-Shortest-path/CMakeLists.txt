cmake_minimum_required(VERSION 2.8)
project(a2ece650)

## ECE650 Specific configuration start here
## Project specific configurations go here

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*, -fuchsia-default-arguments, -google-runtime-references")

# create the main executable
## add additional .cpp files if needed
add_executable(ece650-a2 a2-ece650.cpp parse_line.cpp graph.cpp)