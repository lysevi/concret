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

from matplotlib import rc
rc('font',**{'family':'serif'})
rc('text', usetex=True)
rc('text.latex',unicode=True)
rc('text.latex',preamble='\usepackage[utf8]{inputenc}')
rc('text.latex',preamble='\usepackage[russian]{babel}')

colors="g r w c m y k".split()

f=file(sys.argv[1])
func_name=f.readline().strip()
etalon=np.array(map(lambda s: float(s.strip()),f.readline().split(';')))
etalon=etalon[:24]
gp_results={} # имя алгоритма:[знаяения]
for l in f.readlines():
    splited=l.split(';')
    gp_results[unicode(splited[0],"utf-8")]=np.array(map(float,splited[1:][:24]))

#################################################################
N=len(etalon)
ind = np.arange(N)  # the x locations for the groups
width = 0.15        # the width of the bars

plt.subplot(111)
rects={}
#etalon_rects=plt.bar(ind, etalon, width, color='b')
num=0
print len(etalon)
for k,v in gp_results.items():
    ind=ind+width+width/20.0
    print k,len(v),ind
    rects[k]=plt.bar(ind, abs(etalon-v)/N, width,color=colors[num]) # более красивое
    #rects[k]=plt.bar(ind, v, width,color=colors[num])
    num+=1

plt.ylabel(u'Величина ошибки')
plt.xlabel(u'Номер испытания')
plt.xticks(ind+width, list(range(len(etalon))))

a1=[]#etalon_rects[0]]
a2=[]#func_name]
for k,v in rects.items():
    a1.append(v[0])# ((etalon-gp_results[k])/len(etalon)).sum()
    # abs(gp_results[k]*100/etalon).sum()/N - АРЕ
    error=abs(etalon-gp_results[k])/N
    a2.append(k+' E=%f'%(error.sum()/N))


plt.legend(a1,a2)
if len(sys.argv)==3:
    print sys.argv[-1]
    plt.savefig(sys.argv[-1])
else:
    plt.show()
