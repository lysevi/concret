#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Формат:

Имя функции
значение:значение:...  эталонное значение
имя алгоритма:ошибка:ошибка:...
имя алгоритма2:ошибка:ошибка:...
"""

import sys
import numpy as np
import matplotlib.pyplot as plt

if len(sys.argv)==1:
    print "usage: ",sys.argv[0]," filename"
    sys.exit()

colors="b r g".split()
t="- -- -o".split()

f=file(sys.argv[1])
func_name=f.readline().strip()
etalon=np.array(map(lambda s: float(s.strip()),f.readline().split(';')))
gp_results={} # имя алгоритма:[знаяения]
for l in f.readlines():
    splited=l.split(';')
    gp_results[splited[0]]=np.array(map(float,splited[1:]))

#################################################################

#plt.plot(etalon,"-o")

num=0
print len(etalon)
for k,v in gp_results.items():
    print k,len(v)
    plt.plot(v,t[num],color=colors[num],label=(k+' E=%f Max=%f'%(gp_results[k].sum()/len(etalon),gp_results[k].max()))) # более красивое
    num+=1
plt.legend()
#################################################################

# N=len(etalon)
# ind = np.arange(N)  # the x locations for the groups
# width = 0.15        # the width of the bars

# plt.subplot(111)
# rects={}
# #etalon_rects=plt.bar(ind, etalon, width, color='b')
# num=0
# print len(etalon)
# for k,v in gp_results.items():
#     ind=ind+width+width/20.0
#     print k,len(v),ind
#     rects[k]=plt.bar(ind, abs(v), width,color=colors[num]) # более красивое
#     #rects[k]=plt.bar(ind, v, width,color=colors[num])
#     num+=1

# plt.ylabel(u'Величина ошибки')
# plt.xlabel(u'Номер испытания')
# plt.xticks(ind+width, list(range(len(etalon))))

# a1=[]#etalon_rects[0]]
# a2=[]#func_name]
# for k,v in rects.items():
#     a1.append(v[0])# ((etalon-gp_results[k])/len(etalon)).sum()
#     # abs(gp_results[k]*100/etalon).sum()/N - АРЕ
#     a2.append(k+' E=%f'%(gp_results[k].sum()/len(etalon)))

#plt.legend(a1,a2)
plt.show()
