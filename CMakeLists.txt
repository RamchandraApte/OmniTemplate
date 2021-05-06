cmake_minimum_required(VERSION 3.16)
project(OmniTemplate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(mcss_exe $ENV{HOME}/m.css/documentation/doxygen.py)
add_custom_target(docs COMMAND ${mcss_exe} ${CMAKE_SOURCE_DIR}/docs/conf.py COMMAND python3 ${CMAKE_SOURCE_DIR}/docs/fix_qhp.py COMMAND qhelpgenerator ${CMAKE_SOURCE_DIR}/docs/html/index.qhp COMMENT "Generating documentation using m-css and doxygen")
add_custom_target(test_all COMMAND ${CMAKE_BINARY_DIR}/test DEPENDS test)

add_executable(test src/test/test.cpp)
include_directories(src/ src/graph)
set (CMAKE_CXX_FLAGS "-fmax-errors=2 -Wno-subobject-linkage -Wno-sign-compare -Wno-unused -Wall -Wextra -DDEBUG --coverage -ftest-coverage -fprofile")
set (CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address,undefined -ggdb3 -D_GLIBCXX_DEBUG")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -D_GLIBCXX_ASSERTIONS")
set (CMAKE_EXPORT_COMPILE_COMMANDS True)

target_precompile_headers(test PRIVATE src/core/all.hpp)
