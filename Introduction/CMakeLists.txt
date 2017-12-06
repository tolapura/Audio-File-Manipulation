cmake_minimum_required(VERSION 3.8)
project(proj_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp AudioFile.cpp AudioFile.h)
add_executable(proj_1 ${SOURCE_FILES})