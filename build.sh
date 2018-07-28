#!/usr/bin/env bash

if [ ! -d "build" ]; then
    mkdir -p ./build/
fi

cd build

cmake -Dgtest_force_shared_crt=TRUE ..
cmake --build .