#!/usr/bin/env python

from math import *
import numpy as np

def f(x):
    return ((100*(x+1-x**2))**2+(1-x)**2).sum()

for i in np.arange(0,5,1.0):
    for j in np.arange(0,5,1.0):
        print i,';',j,';',f(np.array([i,j]))
