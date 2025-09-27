# /bin/bash

mkdir -p build && cp -r assets/ build/ && cd build && cmake --build . && ./Game