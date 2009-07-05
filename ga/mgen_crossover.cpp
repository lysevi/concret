#include "mgen_crossover.hpp"

p_dna_vector mgen_crossover::operator()(const p_dna& father,const p_dna& mather)
{
  p_dna_vector result=bin_crossover::operator()(father,mather);
  (*(*result)[0])[(*result)[0]->size()-1]=(*(*result)[0])[(*result)[0]->size()-1]%100;
  (*(*result)[1])[(*result)[1]->size()-1]=(*(*result)[1])[(*result)[1]->size()-1]%100;
  return result;
}
