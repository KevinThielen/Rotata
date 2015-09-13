#!/bin/bash

rm -r webGL
mkdir webGL
cd webGL
cmake .. -DEMSCRIPTEN=1 -DCMAKE_CXX_COMPILER=em++ -DCMAKE_C_COMPILER=emcc 
emmake make
cp ../build/fonts.kte fonts.kte
cp ../build/texture.kte texture.kte
em++ Rubix.bc -o Rubix.html  -s ALLOW_MEMORY_GROWTH=1 -O2 --preload-file ../Resources --embed-file fonts.kte --embed-file texture.kte
python -m SimpleHTTPServer 8080
