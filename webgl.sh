#!/bin/bash

rm -r webGL
mkdir webGL
cd webGL
cmake .. -DEMSCRIPTEN=1 -DCMAKE_CXX_COMPILER=em++ -DCMAKE_C_COMPILER=emcc 
emmake make
cp ../build/KTEData KTEData
cp ../build/Game Game
cp ../build/Menu Menu
cp ../build/GUI GUI
em++ Rubix.bc -o Rubix.html  -s ALLOW_MEMORY_GROWTH=1 -O2 --preload-file ../Resources --embed-file KTEData --embed-file Game --embed-file Menu --embed-file GUI
python -m SimpleHTTPServer 8080
