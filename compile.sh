(cat pre_headers.hpp && g++  -nostdinc -Dinclude=#include -Isystem-headers -UREALGNU -DLOCAL -fdirectives-only -undef -std=c++17 -E $1.cpp) > $1_compiled.cpp
