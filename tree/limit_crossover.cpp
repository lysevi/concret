#include <utils/utils.hpp>
#include <utils/io.hpp>
#include <utils/random.hpp>
#include "tree.hpp"
#include "limit_crossover.hpp"

namespace Tree
{
  LimitCrossover::LimitCrossover(const ivector&limits):m_limits(limits)
  {}

  Tree LimitCrossover::cross(const Tree&tree1,const Tree&tree2)
  {
    Tree r1=tree2.clone();
    Tree r2=tree1.clone();
    // От куда берем поддерево
    ivector r2_numbers=r2.numbers();
    ivector r1_numbers=r1.numbers();
    int st2=get_random_number(r2_numbers,r2);
    // Куда его поставим
    int mp1=get_random_number(r1_numbers,r1);
    r1.set_sub_tree(mp1,r2.sub_tree(st2));
    return r1;
  }
 
  int LimitCrossover::get_random_number(const ivector&numbers,const Tree&tree)const
  {
    int result=numbers[m_rnd.uniform(0,numbers.size()-1)];
    while(in(m_limits.begin(),m_limits.end(),tree.get_node_by_number(result))){
      result=numbers[m_rnd.uniform(0,numbers.size()-1)];
    }
    return result;
  }  
};/// namespace Tree

