#!/bin/bash

rm -r webGL
mkdir webGL
cd webGL
cmake .. -DEMSCRIPTEN=1 -DCMAKE_CXX_COMPILER=em++ -DCMAKE_C_COMPILER=emcc 
emmake make
em++ Rubix.bc -o Rubix.html -s ALLOW_MEMORY_GROWTH=1 -O2 --preload-file ../Resources 
python -m SimpleHTTPServer 8080
