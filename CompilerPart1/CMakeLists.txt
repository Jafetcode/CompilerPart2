cmake_minimum_required(VERSION 3.30)
project(CompilerPart1)

set(CMAKE_CXX_STANDARD 20)

add_executable(CompilerPart1 ../main.cpp
        ../LexAnalyzer.cpp
        LexAnalyzer.h)
