#! /bin/bash

CWD=`pwd`
SUCCESS=0

./script/cleanMoBuild.sh
./script/generateCxxTest.sh
mkdir -p build/mo && cd build/mo
if [ $SUCCESS -eq 0 ]; then
	cmake -D CMAKE_CXX_COMPILER=g++ -D LLVM_SRC_DIR=$CWD/third-party/llvm -D LLVM_BINARY_DIR=$CWD/build/llvm $CWD
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
cd $CWD
if [ $SUCCESS -eq 0 ]; then
	build/mo/bin/mo_test > build/testresults.txt
	if [ $? -ne 0 ]; then
		SUCCESS=3
	fi 
fi 
if [ $SUCCESS -eq 0 ]; then
	python third-party/zcov/zcov-scan build/output.zcov .
	if [ $? -ne 0 ]; then
		SUCCESS=4
	fi
	python third-party/zcov/zcov-genhtml build/output.zcov build/report --root=$CWD/src
	if [ $? -ne 0 ]; then
		SUCCESS=5
	fi
fi 
if [ $SUCCESS -eq 0 ]; then
	if [ -n "$CC_BUILD_ARTIFACTS" ]; then
		mv build/testresults.txt $CC_BUILD_ARTIFACTS/testresults.txt
		mv build/report $CC_BUILD_ARTIFACTS/coverage
	fi
fi
if [ $SUCCESS -eq 0 ]; then
  ./script/samplesDetector.sh > build/samplesinspection.txt
  ./script/selfDetector.sh src/headers/ $CWD/build/llvm/tools/clang/include $CWD/build/llvm/include $CWD/third-party/clang/include $CWD/third-party/llvm/include > build/selfinspection.txt
	if [ -n "$CC_BUILD_ARTIFACTS" ]; then
		mv build/testresults.txt $CC_BUILD_ARTIFACTS/testresults.txt
		mv build/report $CC_BUILD_ARTIFACTS/coverage
		mv build/samplesinspection.txt $CC_BUILD_ARTIFACTS/samplesinspection.txt
		mv build/selfinspection.txt $CC_BUILD_ARTIFACTS/selfinspection.txt
	fi
fi

cd $CWD
exit $SUCCESS