#!/usr/bin/env bash

if [ ! -d "build" ]; then
    mkdir -p ./build/
fi

cd build

cmake -Wdev ../
cmake --build .