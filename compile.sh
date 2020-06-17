(cat pre_headers.hpp && g++  -nostdinc -fdirectives-only -fpreprocessed -std=c++17 -E $1.cpp) > $1_compiled.cpp
