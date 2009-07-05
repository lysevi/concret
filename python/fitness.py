# -*- coding: utf-8 -*-

try:
    import psyco
    psyco.full()
except ImportError:
    print "Running without psyco"

import random

class Fitness:
    def __init__(self,percent_to_learn,input,output7,output):
        self.percent_to_learn=percent_to_learn
        ifile=file(input)

        self.x_matrix=[]
        for line in ifile.readlines():
            w=self.convert_to_dlist(line)
            if len(w)==0:
                continue
            self.x_matrix.append(w)
        
        ifile.close()
        ifile=file(output)
        self.y_vector=self.convert_to_dlist(ifile.readline())
        ifile.close()
        ifile=file(output7)
        self.y_vector7=self.convert_to_dlist(ifile.readline())
        
        self.init()

    def init(self):
        self.numbers=[]
        nums=range(len(self.x_matrix))
        for i in range(int(len(self.x_matrix)*self.percent_to_learn)):
            pos=int(random.uniform(0,len(nums)-1))
            value=nums[pos]
            self.numbers.append(value)
            nums.remove(value)

    def clear(self):
        self.numbers=[]
        self.init()

    def convert_to_dlist(self,line):
        """
        Преобразует строчку в список чисел
        """
        result=[]
        for w in line.split(";"):
            w=w.lstrip()
            if len(w)==0:
                continue

            result.append(float(w.rstrip()))
        return result

    def check_solution(self,d):
        """
        Возвращает отклонение по всей обучающей выборке
        """
        print self.numbers
        result_new=0
        result=0
        for i in range(len(self.x_matrix)):

            v=d.genom.eval({'X1':self.x_matrix[i][0],
                            'X2':self.x_matrix[i][1],
                            'X3':self.x_matrix[i][2],
                            'X4':self.x_matrix[i][3],
                            'X5':self.y_vector7[i]
                            })
            if not i in self.numbers:
                result_new+=(abs(v-self.y_vector[i])/self.y_vector[i])*100
            result+=(abs(v-self.y_vector[i])/self.y_vector[i])*100
            print i,self.y_vector[i]," => ",v
        return result_new/(len(self.x_matrix)-len(self.numbers)),result/(len(self.x_matrix))
    
    def __call__(self,d):
        result=0
        worst_percent=0
        for i in self.numbers:
            v=d.genom.eval({'X1':self.x_matrix[i][0],
                            'X2':self.x_matrix[i][1],
                            'X3':self.x_matrix[i][2],
                            'X4':self.x_matrix[i][3],
                            'X5':self.y_vector7[i]
                            })
            value=abs(v-self.y_vector[i])/self.y_vector[i]*100
            result+=value
            if value>worst_percent:
                worst_percent=value
        return (result/len(self.numbers),worst_percent)
