#ifndef _bin_crossover_
#define _bin_crossover_

#include "crossover.hpp"

class bin_crossover:public crossover
{
public:
  bin_crossover(bool flag=false);
  p_dna_vector operator()(const p_dna& father,const p_dna& mather);
  int cross_two_ints(int a,int b);
protected:
  bool is_canonical; //если true значти одноточечный
};

#endif
