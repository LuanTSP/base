cmake_minimum_required(VERSION 3.14)
project(codebase)

add_library(codebase SHARED
    src/matrix.cpp
)

target_include_directories(codebase
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)