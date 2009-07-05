#ifndef _scheme_dna_generator_
#define _scheme_dna_generator_

#include <ga/schema.hpp>
#include <ga/population.hpp>
#include "bin_dna_generator.hpp"

class scheme_dna_generator:public bin_dna_generator
{
public:
  scheme_dna_generator(bool use_schemes=true);
  p_dna generate();
  scheme_db schemes;
protected:
  bool m_use_schemes;
};


#endif
