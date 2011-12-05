#! /bin/bash

CWD=`pwd`
SUCCESS=0

./script/cleanMoBuild.sh
./script/generateCxxTest.sh
mkdir -p build/oclint && cd build/oclint
if [ $SUCCESS -eq 0 ]; then
	cmake -D IS_CI_BUILD=1 -D CMAKE_CXX_COMPILER=$CWD/build/llvm/bin/clang++ -D LLVM_SRC_DIR=$CWD/third-party/llvm -D LLVM_BINARY_DIR=$CWD/build/llvm $CWD
	if [ $? -ne 0 ]; then
		SUCCESS=1
	fi 
fi 
if [ $SUCCESS -eq 0 ]; then
	make
	if [ $? -ne 0 ]; then
		SUCCESS=2
	fi 
fi
mkdir -p lib/oclint/clang
cp ../llvm/lib/liblibclang.3.1.dylib lib/oclint/clang/
cd $CWD
if [ $SUCCESS -eq 0 ]; then
	build/oclint/bin/oclint_test
	if [ $? -ne 0 ]; then
		SUCCESS=3
	fi 
fi 

cd $CWD
exit $SUCCESS
