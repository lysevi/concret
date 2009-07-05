#ifndef _mgen_crossover_
#define _mgen_crossover_

#include "bin_crossover.hpp"

class mgen_crossover:public bin_crossover
{
public:
  p_dna_vector operator()(const p_dna& father,const p_dna& mather);
};

#endif
