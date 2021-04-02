#!/bin/bash

scripts/update_submodules.sh

if [ -d "build" ]; 
then
	rm -rf build/*
else
    mkdir -p build
fi

cd build

cmake -DDEBUG=ON .. #-DEXT_LIBS=OFF .. 

make -j $(($(nproc) - 1))
