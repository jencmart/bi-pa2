cmake_minimum_required(VERSION 3.6)
project(pa2_cv_02)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp complex.h complex.cpp)
add_executable(pa2_cv_02 ${SOURCE_FILES})