#!/usr/bin/env python

from math import *
import numpy as np


def f(x):
    return x[0]+x[1]-5

for i in np.arange(0,5,0.5):
    for j in np.arange(0,5,0.5):
        print i,';',j,';',f(np.array([i,j]))
