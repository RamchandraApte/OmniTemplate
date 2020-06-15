cmake_minimum_required(VERSION 3.16)
project(OmniTemplate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test test.cpp)

#set (CMAKE_CXX_FLAGS "-DDEBUG -fsanitize=address,undefined -ggdb3")
set (CMAKE_CXX_FLAGS "-g -DLOCAL")

# target_precompile_headers(test PRIVATE template.hpp)
