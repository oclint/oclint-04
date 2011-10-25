#! /bin/bash

CWD=`pwd`
INCLUDES=''
for arg in "$@"
do
  INCLUDES="$INCLUDES -I $arg"
done

for file in `ls -d test/samples/*`
do
  $CWD/build/oclint/bin/oclint $INCLUDES "$file"
done
