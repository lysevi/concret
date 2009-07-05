#include "mgen_mutator.hpp"

mgen_mutator::mgen_mutator(int bit_count):bin_mutator(bit_count)
{}

p_dna mgen_mutator::operator()(const p_dna&d,double percent)
{
  p_dna result(bin_mutator::operator()(d,(*d)[d->size()-1]));
  (*result)[d->size()-1]=(*result)[d->size()-1]%100;
  return result;
}
