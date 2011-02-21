#! /bin/bash

CWD=`pwd`

cd test/samples
for file in `ls -d *`
do
  $CWD/build/bin/mo "$file"
done
