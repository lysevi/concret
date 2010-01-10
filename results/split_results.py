#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
разбивает model_func_results на много файлов и срхраняет их
Формат в файле draw_result.py
"""

import sys

if len(sys.argv)==1:
    print "usage: ",sys.argv[0]," filename"
    sys.exit()

result={} # имя функции:{имя алгоритма:[его результат]}
funcs_y={} # имя функции:[ее выход]

data=file(sys.argv[1]).readlines()
last_loaded_funcs=[]
cur_gp_name=""
cur_name=""
cur_data=[]

for l in data:
    if "gp" in l: # значит название
        if cur_name!="":
            last_loaded_funcs.append(cur_name)
        striped=l.strip()
        splited=striped.split('-')

        cur_gp_name=splited[0].strip()
        cur_name=splited[1].strip()
        first_step=True
    else:
        splited=map(lambda e: e.strip(),l.split(';'))
        if len(splited)==1:
            continue
        func_content=result.get(cur_name,{})
        func_content_alg=func_content.get(cur_gp_name,[])
        func_content_alg.append(splited[-1])
        func_content[cur_gp_name]=func_content_alg
        result[cur_name]=func_content

        if not cur_name in last_loaded_funcs:
            Y=funcs_y.get(cur_name,[])
            Y.append(splited[1])
            funcs_y[cur_name]=Y

# пишем
for k,v in result.items():
    f=file(k+".txt","w")
    f.write(k+'\n')
    f.write((";".join(funcs_y[k]))+'\n')
    for aname in v.keys():
        f.write(aname+';'+(';'.join(v[aname]))+'\n')
    f.close()
