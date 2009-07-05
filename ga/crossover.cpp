#include "crossover.hpp"
#include <utils/utils.hpp>

p_dna_vector crossover::operator()(const p_dna&father,const p_dna&mather)
{
  p_dna_vector  result(new dna_vector(2));
  (*result)[0]=father;
  (*result)[1]=mather;

  for(int i=0;i<father->size();i+=2){
    (*(*result)[0])[i]=(*mather)[i];
    (*(*result)[1])[i]=(*father)[i];
  }

  massert(result->at(0)->size()==result->at(1)->size());
  massert(result->at(0)->size()==father->size());
  return result;
}
