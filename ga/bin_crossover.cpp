#include "bin_crossover.hpp"
#include <utils/utils.hpp>
#include <utils/random.hpp>
#include <bitset>
#include <limits>

using namespace std;

const   short int_size=numeric_limits<int>::digits;
typedef bitset<int_size> int_bitest;

bin_crossover::bin_crossover(bool flag):is_canonical(flag)
{}

p_dna_vector bin_crossover::operator()(const p_dna& father,const p_dna& mather)
{
  p_dna_vector result(new dna_vector);
  result->push_back(father);
  result->push_back(mather);

  if(is_canonical){
    Random r;
    int crv_pos=r.uniform(0,father->size()-1);
    for(int i=0;i<crv_pos;++i){
      int f_gen=(*result->at(0))[i];
      (*result->at(0))[i]=(*result->at(1))[i];
      (*result->at(1))[i]=f_gen;
    }
    return result;
  }
  
  for(int i=0;i<mather->size();i+=2){
    (*result->at(0))[i]=cross_two_ints((*mather)[i],(*father)[i]);
    (*result->at(1))[i]=cross_two_ints((*father)[i],(*mather)[i]);
  }
  
  massert(result->at(0)->size()==result->at(1)->size());
  massert(result->at(0)->size()==father->size());
  return result;
}

int bin_crossover::cross_two_ints(int a,int b)
{
  int_bitest bbs(b);
  int_bitest result(a);
  for(int i=0;i<int_size;i+=2){
    result.set(i,bbs[i]);
  }
  return result.to_ulong();
}
