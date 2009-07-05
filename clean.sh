#!/bin/sh
make clean
find . -name "*~" -exec rm -fv  {} \; 
find . -name "*.orig" -exec rm -fv  {} \; 
find . -name "Makefile" -exec rm -rfv  {} \;
find . -name "CMakeFiles" -exec rm -rfv  {} \;
find . -name "CMakeCache.txt" -exec rm -frv  {} \; 
find . -name "cmake_install.cmake" -exec rm -frv  {} \; 
rm -f clean


