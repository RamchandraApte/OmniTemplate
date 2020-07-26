
.. _program_listing_file_CMakeLists.txt:

Program Listing for File CMakeLists.txt
=======================================

|exhale_lsh| :ref:`Return to documentation for file <file_CMakeLists.txt>` (``CMakeLists.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   cmake_minimum_required(VERSION 3.16)
   project(OmniTemplate)
   
   set(CMAKE_CXX_STANDARD 17)
   set(CMAKE_CXX_STANDARD_REQUIRED True)
   
   add_executable(test test.cpp)
   
   set (CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address,undefined -ggdb3 -D_GLIBCXX_DEBUG")
   set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -D_GLIBCXX_ASSERTIONS -DLOCAL")
   set (CMAKE_EXPORT_COMPILE_COMMANDS True)
   
   # target_precompile_headers(test PRIVATE template.hpp)
