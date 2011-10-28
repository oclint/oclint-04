#! /bin/bash

CWD=`pwd`

INCLUDES=''
for arg in "$@"
do
  INCLUDES="$INCLUDES -I $arg"
done

FILES=''
for file in `ls -d test/samples/*`
do
  FILES="$FILES $file"
done

$CWD/build/oclint/bin/oclint $INCLUDES test/samples/CompilationFail.txt
$CWD/build/oclint/bin/oclint $INCLUDES test/samples/CompilerDiagnostics.cpp test/samples/HelloWorld.m
