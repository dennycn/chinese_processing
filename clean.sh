#!/bin/bash

if [ $# -lt "1" ]; then
    echo usage: $0 [dirname]
    dir=.
else
    dir=$1
fi 

find $dir -iname "CMakeFiles" | xargs rm -rf
find $dir -iname "CMakeCache.txt" | xargs rm 
find $dir -name "cmake_*" | xargs rm 
find $dir -iname "install_manifest.txt" | xargs rm 
find $dir -iname "*.pro" | xargs rm 
find $dir -iname "*.o" | xargs rm 
find $dir -iname "makefile" | xargs rm 

# execute file
rm pinyin/pinyin
