cmake_minimum_required(VERSION 3.10)

project(RubikCube)


# Variables
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SOURCES "${SRC_DIR}/main.cpp" "${SRC_DIR}/cube.cpp")

add_executable(cube ${SOURCES})


# Language settings
set(CMAKE_CXX_STANDARD 11)

# Add include directories
include_directories("${CMAKE_SOURCE_DIR}/include")