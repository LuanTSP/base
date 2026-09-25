cmake_minimum_required(VERSION 3.14)
project(codebase)

add_library(codebase INTERFACE)

target_include_directories(codebase
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)