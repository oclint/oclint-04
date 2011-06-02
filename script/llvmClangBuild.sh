#! /bin/bash

git submodule update --init
cd third-party/llvm/tools
if [ ! -L clang ];
then
  ln -s ../../clang clang
fi
cd ../../../
mkdir -p build/llvm && cd build/llvm
cmake ../../third-party/llvm
make
cd ../../