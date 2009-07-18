#include "population.hpp"
#include "selector.hpp"
#include "hist_gp.hpp"

#include <tree/tree.hpp>
#include <utils/io.hpp>
#include <utils/random.hpp>
#include <tree/generator.hpp>

#include "gp_generator_hist.hpp"

hist_gp::hist_gp(selector*s,mutator*m,crossover*c,bin_dna_generator*g,const int max_hist_size):std_ga(s,m,c,g),
											       m_max_hist_size(max_hist_size)
{
  ((GpGeneratorHist*)m_g)->set_history(&m_history);
}

double hist_gp::oneStep()
{ 
  if(m_history.size()>m_max_hist_size)
    m_history.pop_front();
  
  one_step_values cur_values;
  p_dna bst(best(*cur_population()));

  Tree::Tree t;
  t.flat_to_tree(bst->genom());
  ivector nodes=t.nodes();
  for(int i=0;i<nodes.size();++i){
    if(cur_values.size()<=i)
      cur_values.push_back(ivector());
    cur_values[i].push_back(nodes[i]);
  }

  m_history.push_back(cur_values);
  return std_ga::oneStep();
}
