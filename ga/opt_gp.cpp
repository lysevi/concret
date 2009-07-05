#include "population.hpp"
#include "selector.hpp"
#include "opt_gp.hpp"

#include <tree/tree.hpp>
#include <utils/io.hpp>

opt_gp::opt_gp(selector*s,mutator*m,crossover*c,bin_dna_generator*g,Tree::FunctionDB* fdb):std_ga(s,m,c,g),
											   m_fdb(fdb),
											   m_functions(fdb->functions())
{
  
}

void opt_gp::addIndivid(const p_dna&individ)
{
  LOG("000");
  Tree::Tree tree;
  tree.set_fdb(m_fdb);
  tree.flat_to_tree(individ->genom());
  LOG("Before: "<<tree.to_str()<<' '<<tree.flat());
  tree.compress_const_expr();
  LOG("After: "<<tree.to_str()<<' '<<tree.flat());
  p_dna new_dna(new dna(tree.flat()));
  LOG("DNA="<<new_dna->genom())
  LOG("test");
  std_ga::addIndivid(new_dna);
  LOG("test2");
}
