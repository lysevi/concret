#!/bin/sh

find . -name "*~" -exec rm -fv  {} \;
find . -name "*.pyc" -exec rm -fv  {} \; 



