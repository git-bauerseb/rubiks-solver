cmake_minimum_required(VERSION 3.10)

project(RubikCube)


# Variables
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SOURCES "${SRC_DIR}/main.cpp" 
            "${SRC_DIR}/cube.cpp"
            "${SRC_DIR}/solver.cpp")

add_executable(cube ${SOURCES})


# Language settings
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O3")

# Add include directories
include_directories("${CMAKE_SOURCE_DIR}/include")