cmake_minimum_required(VERSION 3.16)
project(OmniTemplate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test test.cpp)

#set (CMAKE_CXX_FLAGS "-fsanitize=address,undefined -ggdb3 -D_GLIBCXX_DEBUG")
set (CMAKE_CXX_FLAGS "-DLOCAL")
#set(CMAKE_BUILD_TYPE Debug)

# target_precompile_headers(test PRIVATE template.hpp)
