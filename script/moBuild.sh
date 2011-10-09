#! /bin/bash

CWD=`pwd`
SUCCESS=0

./script/cleanMoBuild.sh
./script/generateCxxTest.sh
mkdir -p build/mo && cd build/mo
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
cp ../llvm/lib/liblibclang.3.0.dylib bin/
cd $CWD
if [ $SUCCESS -eq 0 ]; then
	build/mo/bin/mo_test
	if [ $? -ne 0 ]; then
		SUCCESS=3
	fi 
fi 

cd $CWD
exit $SUCCESS