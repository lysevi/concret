#ifndef _ga_gp_mutator_
#define _ga_gp_mutator_

#include <ga/mutator.hpp>
#include <utils/random.hpp>
#include <tree/tree.hpp>
#include <tree/function_db.hpp>
#include <tree/generator.hpp>
#include <tree/crossover.hpp>
#include <tree/mutator.hpp>

class GpMutator:public mutator
{
public:
  GpMutator(Tree::Generator* gnrt,Tree::Crossover*crossover,Tree::FunctionDB*fdb);
  p_dna operator()(const p_dna&d,double percent);
protected:
  Tree::Generator* m_gnrt;
  Tree::Crossover* m_crossover;
  Tree::FunctionDB*m_fdb;
  Tree::Mutator   *m_mtn;
};

#endif
