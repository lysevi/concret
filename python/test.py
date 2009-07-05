#!/usr/bin/env python
# -*- coding: utf-8 -*-

try:
    import psyco
    psyco.full()
except ImportError:
    print "Running without psyco"

import sys
from gp import *

from gp.generator import *
from math import *
import fitness

verbose=True
step_count=100
stop_value=4
psize=400
max_depth=5
percent_to_learn=0.4
run_count=1

if len(sys.argv)!=4:
    print "usage: ",sys.argv[0]," input.csv output_7_day.csv output.csv"
    sys.exit()

fitness=fitness.Fitness(percent_to_learn,sys.argv[1],sys.argv[2],sys.argv[3])

fdb=gp.tree.FunctionDB([make_func(lambda x: x[0]+x[1],2,"+"),             
                        make_func(lambda x: x[0]-x[1],2,"-"),
                        make_func(lambda x: x[0]*x[1],2,"*"),
                        make_func(lambda x: x[0]*x[0],1,"^2"),
                        make_func(lambda x: x[0]/2.0,1,"/2"),
                        make_func(lambda x: sin(x[0]),1,"sin"),
                        make_func(lambda x: cos(x[0]),1,"cos")],
                       vars=[VarNode("X1"),VarNode("X2"),VarNode("X3"),VarNode("X4")
                             ,VarNode("X5")
                             ],consts=[])

gnrt=Generator(fdb,max_depth)
generator=lambda:gp.dna.Dna(gnrt.generate(),-1)
s=selector.RandomSelector()

a=gp.A.A(crossover=crossover.crossover,
         mutator=gp.mutator.Mutator(generator),
         selector=lambda p,c: s.select(p,c),
         size=psize,
         elite=True,
         controller=gp.controller.Controller(0.7,psize))

a.fitness=fitness
a.generator=generator

for i in range(run_count):
    print "Step=",i
    a.init()
    result=a.solution(step_count=step_count,stop_value=stop_value,verbose=verbose)
    best_solution=result[1]
    print "Best solution: ",fitness.check_solution(best_solution)
    a.clean()
