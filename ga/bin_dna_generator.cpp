#include "bin_dna_generator.hpp"
#include <utils/utils.hpp>
#include <utils/binary.hpp>

bin_dna_generator::bin_dna_generator(float from,float to,int size):m_from(from),
								   m_to(to),
								   m_size(size)
{}

bin_dna_generator::bin_dna_generator()
{}

p_dna bin_dna_generator::generate()
{
  p_dna result(new dna(m_size));
  for(int i=0;i<m_size;++i){
    float value=m_rnd.uniform(m_from,m_to);
    (*result)[i]=real2bin(value);
  }
  massert(result->size()==m_size);
  return result;
}

void bin_dna_generator::setSize(int s)
{
  m_size=s;
}

void bin_dna_generator::setFrom(int f)
{
  m_from=f;
}

void bin_dna_generator::setTo(int t)
{
  m_to=t;
}

int bin_dna_generator::size()const
{
  return m_size;
}
