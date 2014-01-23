#! /bin/bash

MAJOR_VERSION=0.4.3
AUTO_INCREASE_VERSION=`git log --oneline | wc -l | sed 's/ //g'`
CURRENT_VERSION="$MAJOR_VERSION.$AUTO_INCREASE_VERSION"
OCLINT_CURRENT_VERSION="oclint.$CURRENT_VERSION"

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
  mkdir -p lib/oclint/clang
  cp ../llvm/lib/liblibclang.3.1.dylib lib/oclint/clang/
  cp -r ../llvm/lib/clang/3.1/include lib/oclint/clang/
  mkdir -p "$INSTALLATION_PATH/$OCLINT_CURRENT_VERSION"
  cp -r bin "$INSTALLATION_PATH/$OCLINT_CURRENT_VERSION/bin"
  cp -r lib "$INSTALLATION_PATH/$OCLINT_CURRENT_VERSION/lib"
  mkdir -p resources
  head -n 28 ../../LICENSE | tail -n 24 > resources/License.txt
  /Developer/usr/bin/packagemaker --title "OCLint" --version $CURRENT_VERSION --filter "\.DS_Store" --root-volume-only --domain system --verbose --no-relocate -l /usr --id org.oclint.pkg --root "$INSTALLATION_PATH/$OCLINT_CURRENT_VERSION" --resources ./resources --out "$INSTALLATION_PATH/oclint-$CURRENT_VERSION.pkg"
  cd "$INSTALLATION_PATH"
  zip -r "oclint-$MAJOR_VERSION.pkg.zip" "oclint-$CURRENT_VERSION.pkg"
fi
cd $CWD
exit $SUCCESS
