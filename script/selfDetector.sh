#! /bin/bash

CWD=`pwd`

INCLUDES=''
for arg in "$@"
do
  INCLUDES="$INCLUDES -I $arg"
done

FILES=''
for file in `find src -name *.cpp`
do
  FILES="$FILES $file"
done

$CWD/build/oclint/bin/oclint -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS $INCLUDES $FILES
