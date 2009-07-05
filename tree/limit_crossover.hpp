#ifndef _limit_tree_crossover_hpp_
#define _limit_tree_crossover_hpp_

#include <tree/crossover.hpp>

namespace Tree
{
  /* 
     Кроссовер с ограничениями.
     Передается вектор номеров узлов, в которых не должно происходить скрещивание.
   */
  class LimitCrossover:public Crossover
  {
  public:
    LimitCrossover(const ivector&limits);
    Tree cross(const Tree&tree1,const Tree&tree2);
    int get_random_number(const ivector&numbers,const Tree&tree)const;
  protected:
    ivector m_limits;
  };
};//namespace Tree

#endif
