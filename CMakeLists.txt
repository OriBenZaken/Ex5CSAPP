cmake_minimum_required(VERSION 3.8)
project(untitled3)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES library.c library.h myfunction.c readBMP.h readBMP.c writeBMP.c writeBMP.h)
add_executable(Main ${SOURCE_FILES} showBMP.c)
add_library(untitled3 ${SOURCE_FILES})