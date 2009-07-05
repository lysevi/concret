#include <utils/random.hpp>

#include <tree/tree.hpp>
#include <tree/crossover.hpp>
#include <tree/function_db.hpp>

#include "gp_crossover.hpp"

GpCrossover::GpCrossover(Tree::FunctionDB*fdb,Tree::Crossover*crv):m_fdb(fdb),
								   m_crv(crv)
{}

p_dna_vector GpCrossover::operator()(const p_dna&father,const p_dna&mather)
{
  p_dna_vector result(new dna_vector(1));
  Tree::Tree father_tree;
  Tree::Tree mather_tree;

  father_tree.set_fdb(m_fdb);
  father_tree.flat_to_tree(father->genom());
  
  mather_tree.set_fdb(m_fdb);
  mather_tree.flat_to_tree(mather->genom());

  Tree::Tree result_tree=m_crv->cross(father_tree,mather_tree);
  if(result_tree.size()<=father_tree.size())
    result->at(0)=p_dna(new dna(result_tree.flat()));
  else
    result->at(0)=p_dna(new dna(father->genom()));
  return result;
}
