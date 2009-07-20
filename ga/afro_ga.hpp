#ifndef _afro_ga_
#define _afro_ga_

#include <ga/std_ga.hpp>

class afro_ga:public std_ga
{
public:
  afro_ga(selector*s,mutator*m,crossover*c,bin_dna_generator*g);
  void init();
  void addIndivid(const p_dna&individ);
  family_vector select(const population&p,const ivector&chanches,int count);
  double oneStep();
  solution getSolution(int max_steps,double min_ftn,bool verbose);
protected:
  ivector m_chanches[2]; // шанс на скрещивание i-го индивида из соотвествующей популяции.
  int     m_cur_chanches;
};

#endif
