#!/bin/sh
mkdir build
cd build

cmake -G "Unix Makefiles" ..
make

file=../output.txt
echo >$file
for i in 8 7 6 5 4 3 2 1
do
    echo =================================start $i treads >> $file
    ./integral ../input.txt $i >> $file
done

