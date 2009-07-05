#include "gp_mutator.hpp"

GpMutator::GpMutator(Tree::Generator* gnrt,Tree::Crossover*crossover,Tree::FunctionDB*fdb):m_gnrt(gnrt),
											   m_crossover(crossover),
											   m_fdb(fdb)
{
  m_mtn=new Tree::Mutator(m_gnrt,m_crossover);
}


p_dna GpMutator::operator()(const p_dna&d,double percent)
{
  if(this->percent()>percent)
    return d;

  Tree::Tree d_tree;
  d_tree.set_fdb(m_fdb);
  d_tree.flat_to_tree(d->genom());
  Tree::Tree result_tree=m_mtn->mutate(d_tree,percent);
  if (result_tree.size()<=d_tree.size())
    return p_dna(new dna(result_tree.flat()));
  else
    return p_dna(new dna(d->genom()));
}
