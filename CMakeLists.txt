cmake_minimum_required(VERSION 3.5)
project(multipro)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


find_package( OpenCL REQUIRED )

include_directories("/home/kannadan/CLionProjects/multipro/lodepng")

include_directories( ${OPENCL_INCLUDE_DIR} )


add_executable(multipro main.cpp lodepng/lodepng.cpp)
target_link_libraries(multipro ${OPENCL_LIBRARIES})

