#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Косвенный нечеткий вывод (Ермоленко)


def ermolka(X,Y):
    # Агрегирование
    agr=[]
    for x in X:
        cur_x=x[0]
        for i in range(len(x)):
            cur_x=max(x[i],cur_x)
        agr.append(cur_x)
    print "AGR:",agr
    # Активация
    akt=[]
    for i in range(len(Y)):
        akt.append(max((1-agr[i]),Y[i]))
    print "AKT:",akt
    
    return 0;

X=[[0.9,0.8],
   [0.2,0.3],
   [0.5,0.9]
   ]

Y=[0.9,0.2,0.5]

print "X:",X
print "\nY:",Y,'\n'

ermolka(X,Y)
