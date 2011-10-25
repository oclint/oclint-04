#! /bin/bash

MAJOR_VERSION=0.2.4
AUTO_INCREASE_VERSION=`git log --oneline | wc -l | sed 's/ //g'`
CURRENT_VERSION="oclint.$MAJOR_VERSION.$AUTO_INCREASE_VERSION"

SUCCESS=0
INSTALLATION_PATH=$1
if [ "$1" == "" ]; then
    echo "Please specify your installation path"
    SUCCESS=3
fi

CWD=`pwd`

if [ $SUCCESS -eq 0 ]; then
  ./script/cleanMoBuild.sh
  mkdir -p build/oclint && cd build/oclint
	cmake -D CMAKE_CXX_COMPILER=$CWD/build/llvm/bin/clang++ -D LLVM_SRC_DIR=$CWD/third-party/llvm -D LLVM_BINARY_DIR=$CWD/build/llvm $CWD
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
if [ $SUCCESS -eq 0 ]; then
  cp ../llvm/lib/liblibclang.3.0.dylib bin/ 
  mkdir -p "$INSTALLATION_PATH/$CURRENT_VERSION"
  cp -r bin/* "$INSTALLATION_PATH/$CURRENT_VERSION"
fi
cd $CWD
exit $SUCCESS