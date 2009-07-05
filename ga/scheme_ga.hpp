#ifndef _scheme_ga_
#define _scheme_ga_

#include <ga/std_ga.hpp>
#include <ga/niche.hpp>
#include <ga/schema.hpp>
class scheme_dna_generator;


class scheme_ga:public std_ga
{
public:
  scheme_ga(selector*s,mutator*m,crossover*c,scheme_dna_generator*g,bool use_mutator=true);
  void   init();
  int call_nums;
  dna_cmeans cm;
protected:
  scheme_db select_schemes();
  bool      m_use_mutator; // использовать ли специальный мутатор
};

#endif
