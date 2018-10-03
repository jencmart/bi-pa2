cmake_minimum_required(VERSION 3.6)
project(complex)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp complex.cpp)
add_executable(complex ${SOURCE_FILES})