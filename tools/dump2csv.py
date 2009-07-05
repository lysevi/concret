#!/usr/bin/env python
# -*- coding: utf-8 -*-
#  Преобразует дамп к следующему виду:
#  сренее значание фитнесса ; номер популяции

 
import sys

if(len(sys.argv)!=3):
    print "usage:\n\t",sys.argv[0],"path_to_source_file dot_count"
    sys.exit()

src=file(sys.argv[1])

lines=src.readlines()
cnt=int(sys.argv[2])
pos=0

while pos<len(lines):
    splited=lines[pos].split(';')
    splited=splited[:-1]
    n=int(splited[0])
    ftns=map(float,splited[1:])
    r=reduce(lambda x,y: x+y,ftns)/len(ftns)
    print r,';',n
    pos+=int(len(lines)/cnt)

splited=lines[-1].split(';')
splited=splited[:-1]
n=int(splited[0])
ftns=map(float,splited[1:])
r=reduce(lambda x,y: x+y,ftns)/len(ftns)
print r,';',n
