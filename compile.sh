(cat pre_headers.hpp && g++  -nostdinc -Dinclude=#include -Isystem-headers -UREALGNU -fdirectives-only -undef -std=c++17 -E test.cpp) > single_file.cpp
