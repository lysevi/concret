#include <utils/random.hpp>
#include <tree/tree.hpp>
#include <tree/generator.hpp>

#include "gp_generator.hpp"

GpGenerator::GpGenerator(Tree::Generator*gnrt):m_generator(gnrt)
{}

p_dna GpGenerator::generate()
{
  Tree::Tree rnd_tree=m_generator->generate();
  ivector flat_tree=rnd_tree.flat();
  p_dna result(new dna(flat_tree));
  return result;
}
