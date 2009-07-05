#ifndef _mgen_mutator_
#define _mgen_mutator_

#include "bin_mutator.hpp"

class mgen_mutator:public bin_mutator
{
public:
  mgen_mutator(int bit_count);
  p_dna operator()(const p_dna&d,double percent);
};

#endif
