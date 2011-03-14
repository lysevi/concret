#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import numpy as np
import matplotlib.pyplot as plt

colors="g r w c m y k".split()


def not_empty(s):
    return len(s)>0

def strip_all(seq):
    return map(lambda x:x.strip(),seq)


if len(sys.argv)==1:
    print "usage: ",sys.argv[0]," file"
    sys.exit()

from matplotlib import rc
rc('font',**{'family':'serif'})
rc('text', usetex=True)
rc('text.latex',unicode=True)
rc('text.latex',preamble='\usepackage[utf8]{inputenc}')
rc('text.latex',preamble='\usepackage[russian]{babel}')

in_file=file(sys.argv[1])
ga_name=in_file.readline()
print ga_name.strip()

names=[]
values=[]
for line in in_file.readlines():
    sl=filter(not_empty,strip_all(line.split(';')))
    names.append(unicode(sl[0],"utf-8"))
    values.append([int(sl[1])])

print "GA: ",names
print "Values: ",values

#################################################################
N=1
ind = np.arange(N)  # the x locations for the groups
width = 0.15        # the width of the bars

plt.subplot(111)
rects={}
num=0
print len(values)
for i in range(len(values)):
    ind=ind+width+width/20.0
    print "v=",values[i]
    rects[i]=plt.bar(ind, values[i], width,color=colors[num]) # более красивое
    num+=1

plt.ylabel(u'Количество поколений')
plt.xlabel(u'Алгоритм')
plt.xticks(ind-width, map(lambda x: ' ',list(range(len(names)))))

a1=[]
a2=[]
for k,v in rects.items():
    a1.append(v[0])
    a2.append(names[k]+' D='+str(values[k][0]))

plt.legend(a1,a2)
plt.show()
