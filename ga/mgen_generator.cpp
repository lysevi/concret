#include "mgen_generator.hpp"
#include <utils/binary.hpp>
#include <utils/random.hpp>

p_dna mgen_dna_generator::generate()
{
  Random rnd;
  p_dna result(new dna(m_size+1));
  p_dna rnd_dna(bin_dna_generator::generate());
  for(int i=0;i<m_size;++i)
    (*result)[i]=(*rnd_dna)[i];
  (*result)[m_size]=real2bin(rnd.uniform(0.0,50.0));
  return result;
}
