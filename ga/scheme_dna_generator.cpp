#include "scheme_dna_generator.hpp"
#include <utils/utils.hpp>
#include <utils/binary.hpp>
#include <utils/io.hpp>

scheme_dna_generator::scheme_dna_generator(bool use_schemes):m_use_schemes(use_schemes)
{}

p_dna scheme_dna_generator::generate()
{
  if((schemes.size()==0)||(!m_use_schemes)){
    return bin_dna_generator::generate();
  }
  
  // Ищем схему с лучшим фитнесом
  symbol_list scheme=bestSchema(schemes);

  p_dna new_gv(new dna(m_size));
  ivector not_empty_els;// места,куда нельзя сгенерировать случайное число :)
  for(symbol_list::const_iterator s_pos=scheme.begin();s_pos!=scheme.end();++s_pos){
    if(s_pos->second!=-1){
      (*new_gv)[s_pos->second]=s_pos->first;
      not_empty_els.push_back(s_pos->second);
    }
  }
  sort(not_empty_els.begin(),not_empty_els.end());
  
  int next_know=0;
  for(int i=0;i<m_size;++i){
    if(i==not_empty_els[next_know]){
      next_know++;
      continue;
    }
    float value=m_rnd.uniform(m_from,m_to);
    (*new_gv)[i]=real2bin(value);
  }
  
  return new_gv;
}
