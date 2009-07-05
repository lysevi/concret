#ifndef _ga_gp_generator_
#define _ga_gp_generator_

#include <ga/bin_dna_generator.hpp>

class GpGenerator:public bin_dna_generator
{
public:
  GpGenerator(Tree::Generator*gnrt);
  p_dna generate();
protected:
  Tree::Generator *m_generator;
};

#endif
