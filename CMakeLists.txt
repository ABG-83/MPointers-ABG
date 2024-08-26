cmake_minimum_required(VERSION 3.29)
project(MPointers_ABG)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(MPointers_ABG
    include/MPointer.h
    include/MPointerGC.h
    src/main.cpp
    src/MPointer.cpp
    src/MPointerGC.cpp)
