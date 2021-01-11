DIR=$(dirname "$0")
(cat $DIR/pre_headers.hpp && (g++  -nostdinc -DPRE -fdirectives-only -I$DIR/src -std=c++17 -E $1.cpp ${@:2} | grep -A100000000 "#define PRE 1")) > $1_compiled.cpp
