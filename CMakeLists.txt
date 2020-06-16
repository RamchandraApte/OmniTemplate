cmake_minimum_required(VERSION 3.16)
project(OmniTemplate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test test.cpp)

set (CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address,undefined -ggdb3 -D_GLIBCXX_DEBUG")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -D_GLIBCXX_ASSERTIONS -DLOCAL")

# target_precompile_headers(test PRIVATE template.hpp)
