#ifndef _bin_mutator_
#define _bin_mutator_

#include "mutator.hpp"

class bin_mutator:public mutator
{
public:
  bin_mutator(int bit_count);
  p_dna operator()(const p_dna&d,double percent);
  int int_mutate(int a,double percent);
protected:
  int m_bit_count;
};

#endif
