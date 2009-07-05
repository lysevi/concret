#include "bin_mutator.hpp"

#include <bitset>
#include <limits>

using namespace std;

const   short int_size=numeric_limits<int>::digits;
typedef bitset<int_size> int_bitest;

bin_mutator::bin_mutator(int bit_count):m_bit_count(bit_count)
{}

p_dna bin_mutator::operator()(const p_dna&d,double prc)
{
  p_dna result(new dna(*d));
  for(int i=0;i<d->size();i++){
    if(percent()<prc)
      (*result)[i]=int_mutate((*result)[i],prc);
  }
  assert(result->size()==d->size());
  return result;
}

int  bin_mutator::int_mutate(int a,double prc)
{
  double n_percent=prc;
  int_bitest bs(a);
  for(int i=0;i<m_bit_count;i++){
    if(percent()<n_percent)
      bs.set(i,!bs[i]);
    n_percent/=i;
  }
  return bs.to_ulong();
}
