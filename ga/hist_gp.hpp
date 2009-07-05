#ifndef _hist_ga_
#define _hist_ga_

#include <ga/std_ga.hpp>

#include "history.hpp"

class hist_gp:public std_ga
{
public:
  hist_gp(selector*s,mutator*m,crossover*c,bin_dna_generator*g,const int max_hist_size);
  double oneStep();
  int     m_max_hist_size;
  history m_history;
};

#endif
