cmake_minimum_required(VERSION 3.13)
project(multipro)

set(CMAKE_CXX_STANDARD 14)

include_directories("/home/kannadan/CLionProjects/multipro/lodepng")

add_executable(multipro main.cpp lodepng/lodepng.cpp)
