#include "dna.hpp"
#include "population.hpp"
#include <iterator>

#include <utils/io.hpp>

p_dna  worst(const population&p)
{
  population::const_iterator pos=p.begin();
  p_dna result=*pos;
  while(pos!=p.end()){
    if((*pos)->ftn()>result->ftn())
      result=*pos;
    ++pos;
  }
  return result;
}

p_dna  best(const population&p)
{
  population::const_iterator pos=p.begin();
  p_dna result=*pos;
  while(pos!=p.end()){
    if((*pos)->ftn()<result->ftn())
      result=*pos;
    ++pos;
  }
  return result;
}

p_dna byIndex(const population&p,int index)
{
  massert(index>p.size());
  return p[index];
}

int    indexOfBest(const population&p)
{
  population::const_iterator pos=p.begin();
  p_dna result=*pos;
  int result_index=0;
  int cur=0;
  while(pos!=p.end()){
    if((*pos)->ftn()<result->ftn()){
      result=*pos;
      result_index=cur;
    }
    ++pos;
    ++cur;
  }
  return result_index;
}
