#ifndef _tree_mutator_hpp
#define _tree_mutator_hpp

class Random;

namespace Tree
{
  class Mutator
  {
  public:
    Mutator(Generator* gnrt,Crossover*crossover);
    Tree mutate(const Tree&t,double percent);
  protected:
    Random m_rnd;
    Generator *m_generator;
    Crossover *m_crossover;
  };
};

#endif
