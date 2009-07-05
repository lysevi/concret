#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Упрощенный алгоритм нечеткого вывода (Сугено)

myu_x=[
    [0.9,0.8],
    [0.1,0.1],
    [0.9,0.2]
    ]

c=[100,3,40]

alphas=map(lambda x: min(x),myu_x)
y=c[:]
up=0
down=0
for i in range(len(alphas)):
    up+=alphas[i]*y[i]
    down+=alphas[i]
result=up/down
print "Myu(X)=",myu_x
print "C=",c
print result
