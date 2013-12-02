#! /bin/bash

# Retrieve llvm and clang as submodule
git submodule update --init
cd third-party/llvm
# Checkout Release 3.1 of llvm
git checkout origin/release_31
cd ../clang
# Checkout Release 3.1 of clang
git checkout origin/release_31

cd ../llvm/tools
if [ ! -L clang ];
then
  ln -s ../../clang clang
fi
cd ../../../
mkdir -p build/llvm && cd build/llvm
cmake ../../third-party/llvm
make
install_name_tool -id @executable_path/../lib/oclint/clang/liblibclang.3.1.dylib lib/liblibclang.3.1.dylib
# Name seems to changed in next release of clang
#install_name_tool -id @executable_path/../lib/oclint/clang/lib/libclang.3.1.dylib lib/libclang.3.1.dylib
cd ../../
