cmake_minimum_required(VERSION 3.16)
project(OmniTemplate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test test.cpp)

set (CMAKE_CXX_FLAGS "-DDEBUG")

# target_precompile_headers(test PRIVATE template.hpp)
