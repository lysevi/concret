#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Формат:

Имя функции
значение:значение:...  эталонное значение
имя алгоритма:значение:значение:...
имя алгоритма2:значение:значение:...
"""

import sys
import numpy as np
import matplotlib.pyplot as plt

if len(sys.argv)==1:
    print "usage: ",sys.argv[0]," filename"
    sys.exit()

colors="g r c m y k w".split()

f=file(sys.argv[1])
func_name=f.readline().strip()
etalon=np.array(map(lambda s: float(s.strip()),f.readline().split(';')))
gp_results={} # имя алгоритма:[знаяения]
for l in f.readlines():
    splited=l.split(';')
    gp_results[splited[0]]=np.array(map(float,splited[1:]))

#################################################################
N=len(etalon)
ind = np.arange(N)  # the x locations for the groups
width = 0.25        # the width of the bars

plt.subplot(111)
rects={}
rects[func_name]=plt.bar(ind, etalon, width, color='b')
num=0
for k,v in gp_results.items():
    ind=ind+width
    rects[k]=plt.bar(ind, v, width,color=colors[num])
    num+=1

plt.ylabel(u'Выходное значение')
plt.xticks(ind+width, list(range(len(etalon))))

a1=[]
a2=[]
for k,v in rects.items():
    a1.append(v[0])
    a2.append(k)
plt.legend(a1,a2)
plt.show()