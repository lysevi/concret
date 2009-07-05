#ifndef _mgen_dna_generator_
#define _mgen_dna_generator_

#include <ga/population.hpp>
#include "bin_dna_generator.hpp"

class mgen_dna_generator:public bin_dna_generator
{
public:
  p_dna generate();
};


#endif
