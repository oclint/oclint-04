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
cp -r ../llvm/lib/clang/3.1/include lib/oclint/clang/
if [ $SUCCESS -eq 0 ]; then
	cp -r ../../test/samples test/samples
	./bin/oclint_test > ../testresults.txt
	mkdir coverage
	rm src/impl/oclint/rule/CMakeFiles/UnusedLocalVariableRule.dir/UnusedLocalVariableRule.cpp.gcno
	rm src/impl/oclint/rule/CMakeFiles/UnusedMethodParameterRule.dir/UnusedMethodParameterRule.cpp.gcno
	rm src/impl/oclint/rule/CMakeFiles/UnreachableCodeRule.dir/UnreachableCodeRule.cpp.gcno
	rm src/impl/oclint/rule/CMakeFiles/NPathComplexityRule.dir/NPathComplexityRule.cpp.gcno
	rm src/impl/oclint/rule/CMakeFiles/RedundantIfStatementRule.dir/RedundantIfStatementRule.cpp.gcno
	rm src/impl/oclint/rule/CMakeFiles/RedundantLocalVariableRule.dir/RedundantLocalVariableRule.cpp.gcno
	for file in `find . -name '*.gcda'`; do mv $file coverage/; done
	for file in `find . -name '*.gcno'`; do mv $file coverage/; done
	if [ $? -ne 0 ]; then
		SUCCESS=3
	fi 
fi 
cd $CWD
if [ $SUCCESS -eq 0 ]; then
	lcov -b . -d . -c -o build/output.lcov
	if [ $? -ne 0 ]; then
		SUCCESS=4
	fi
	lcov -e build/output.lcov "$CWD/src/*" -o build/output.lcov
	if [ $? -ne 0 ]; then
		SUCCESS=6
	fi
	genhtml -o build/report -t "OCLint test coverage" --num-spaces 4 build/output.lcov
	if [ $? -ne 0 ]; then
		SUCCESS=7
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
rm -rf CMakeFiles
exit $SUCCESS
