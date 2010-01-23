#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Разбивает результаты ГА.
"""

import sys

def not_empty(s):
    return len(s)>0

def strip_all(seq):
    return map(lambda x:x.strip(),seq)

if len(sys.argv)==1:
    print "usage: ",sys.argv[0]," file"
    sys.exit()

in_file=file(sys.argv[1])
ga_names=filter(not_empty,strip_all(in_file.readline().split('\t')))
print ga_names
results={} # имя теста -> [результаты]
for line in in_file.readlines():
    sl=filter(not_empty,strip_all(line.split('\t')))
    results[sl[0]]=sl[1:]

for test in results.keys():
    fname="ga-"+test+".txt"
    print "writing ",fname,'...'
    out=open(fname,"w")
    out.write(test+"\n")
    for i in range(len(ga_names)):
        out.write(ga_names[i]+';'+results[test][i]+'\n')
    out.close()
