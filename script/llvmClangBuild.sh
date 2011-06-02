#! /bin/bash

git submodule update --init
cd third-party/llvm/tools
rm clang && ln -s ../../clang clang
cd ../../../
mkdir -p build/llvm && cd build/llvm
cmake ../../third-party/llvm
make
cd ../../