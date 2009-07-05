#ifndef _opt_ga_
#define _opt_ga_

#include <ga/std_ga.hpp>
#include <ga/niche.hpp>

#include <tree/node.hpp>
#include <tree/function_db.hpp>

#include <utils/utils.hpp>

class opt_gp:public std_ga
{
public:
  opt_gp(selector*s,mutator*m,crossover*c,bin_dna_generator*g,Tree::FunctionDB* fdb);
  void addIndivid(const p_dna&individ);
protected:
  Tree::FunctionDB* m_fdb;
  ivector m_functions;
};

#endif
