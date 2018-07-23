#!/usr/bin/env bash

if [ ! -d "build" ]; then
    mkdir -p ./build/
fi

cd build

cmake -DGTEST_LINKED_AS_SHARED_LIBRARY=1 -Wdev ../
cmake -DGTEST_LINKED_AS_SHARED_LIBRARY=1 --build .
