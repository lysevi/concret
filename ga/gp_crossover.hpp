#ifndef _ga_gp_crossover_
#define _ga_gp_crossover_

#include <ga/crossover.hpp>

class GpCrossover:public crossover
{
public:
  GpCrossover(Tree::FunctionDB*fdb,Tree::Crossover*crv);
  p_dna_vector operator()(const p_dna&father,const p_dna&mather);
protected:
  Tree::FunctionDB*m_fdb;
  Tree::Crossover *m_crv;
};

#endif
