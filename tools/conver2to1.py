#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Преобразует 3 csv файла в один

import sys

if len(sys.argv)!=4:
    print "usage: ",sys.argv[0],' file1 file2 file3'
    sys.exit()

f1=open(sys.argv[1])
f2=open(sys.argv[2])
f3=open(sys.argv[3])

f1_content=f1.readlines()
f2_content=f2.readlines()[0].split(';')
f3_content=f3.readlines()[0].split(';')

for i in range(len(f1_content)):
    print f1_content[i].split('\n')[0].strip(),';',f2_content[i].split('\n')[0].strip(),';',f3_content[i].strip()


