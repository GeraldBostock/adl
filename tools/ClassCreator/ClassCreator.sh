#!/bin/sh

read -p 'ClassName: ' className
read -p 'Path: ../../source/?' dirPath

echo ../../source/$dirPath/$ClassName.cpp

echo "\ncpp"
cat "Templates/cppTemplate.txt" | sed -e "s/\${Class}/${className}/g" | tee ../../source/$dirPath/$className.cpp
echo "\nh"
cat "Templates/hTemplate.txt" | sed -e "s/\${Class}/${className}/g" | tee ../../source/$dirPath/$className.h


#while read line
#do
#    eval echo "$line"
#done < "./Templates/cppTemplate.txt"
