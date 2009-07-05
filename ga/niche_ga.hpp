#ifndef _niche_ga_
#define _niche_ga_

#include <ga/std_ga.hpp>
#include <ga/niche.hpp>

class niche_ga:public std_ga
{
public:
  niche_ga(selector*s,mutator*m,crossover*c,bin_dna_generator*g);
  family_vector select(const population&p,int count);
  dna_cmeans cm;
  int call_nums;
};

#endif
