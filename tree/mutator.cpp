#include <utils/random.hpp>
#include "tree.hpp"

#include "generator.hpp"
#include "crossover.hpp"
#include "mutator.hpp"

namespace Tree
{
  Mutator::Mutator(Generator* gnrt,Crossover*crossover):m_generator(gnrt),
							m_crossover(crossover)
  {}
  
  Tree Mutator::mutate(const Tree&t,double percent)
  {
    Tree rnd_tree=m_generator->generate();
    return m_crossover->cross(t,rnd_tree);
  }
};
