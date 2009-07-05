#ifndef _tree_crossover_hpp_
#define _tree_crossover_hpp_

class Random;

namespace Tree
{
  class Crossover
  {
  public:
    virtual Tree cross(const Tree&tree1,const Tree&tree2);
    virtual int get_random_number(const ivector&numbers)const;
  protected:
    Random m_rnd;
  };
};//namespace Tree

#endif
