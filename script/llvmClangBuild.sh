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
install_name_tool -id @executable_path/liblibclang.3.0.dylib lib/liblibclang.3.0.dylib
cd ../../