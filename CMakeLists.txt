cmake_minimum_required(VERSION 3.28)
project(CompilerPart1)

set(CMAKE_CXX_STANDARD 17)

add_executable(CompilerPart1 main.cpp
        cmake-build-debug/LexAnalyzer.cpp
        cmake-build-debug/LexAnalyzer.h)
