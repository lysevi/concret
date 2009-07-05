#include <utils/utils.hpp>
#include <utils/random.hpp>
#include "tree.hpp"
#include "crossover.hpp"

namespace Tree
{
  Tree Crossover::cross(const Tree&tree1,const Tree&tree2)
  {
    Tree r1=tree2.clone();
    Tree r2=tree1.clone();
    // От куда берем поддерево
    ivector r2_numbers=r2.numbers();
    ivector r1_numbers=r1.numbers();
    int st2=get_random_number(r2_numbers);
    // Куда его поставим
    int mp1=get_random_number(r1_numbers);
    r1.set_sub_tree(mp1,r2.sub_tree(st2));

    return r1;
  }
  
  int Crossover::get_random_number(const ivector&numbers)const
  {
    return numbers[m_rnd.uniform(0,numbers.size()-1)];
  }
};/// namespace Tree
