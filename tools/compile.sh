set -euo pipefail
shopt -s inherit_errexit
DIR=$(dirname "$0")/..
outfile=${1%%.*}_compiled.cpp
(grep -B10000000 '#endif // PRE' $DIR/src/core/all.hpp && (g++  -nostdinc -DPRE -fdirectives-only -I$DIR/src -std=c++17 -E $1 ${@:2} | grep -A100000000 "#define PRE 1")) > $outfile || rm $outfile
