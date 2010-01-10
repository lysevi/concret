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

colors="g r m y".split()
line_style='-- -. : ,'.split()

f=file(sys.argv[1])
func_name=f.readline().strip()
etalon=np.array(map(lambda s: float(s.strip()),f.readline().split(';')))
gp_results={} # имя алгоритма:[знаяения]
for l in f.readlines():
    splited=l.split(';')
    gp_results[splited[0]]=np.array(map(float,splited[1:]))

#################################################################
N=len(etalon)
x = np.arange(N)  # the x locations for the groups

plt.subplot(111)

plt.plot(x,etalon,"bo-",label=func_name)
num=0
for k,v in gp_results.items():
    print x,v
    plt.plot(x,v,colors[num]+line_style[num],label=k)
    num+=1

plt.ylabel(u'$f(x)$')
plt.xlabel(u'$x$')

plt.legend()
plt.show()
