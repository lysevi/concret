#include "scheme_mutator.hpp"
#include <utils/utils.hpp>

scheme_mutator::scheme_mutator(int bit_count):bin_mutator(bit_count)
{}

void scheme_mutator::set_scheme_db(const scheme_db&sdb)
{
  m_sdb=sdb;
}

bool scheme_mutator::in_scheme(int value,int pos)const
{
  for(scheme_db::const_iterator pos=m_sdb.begin();pos!=m_sdb.end();++pos){
    symbol_list::const_iterator s_pos=pos->symbols.begin();
    for(;s_pos!=pos->symbols.end();++s_pos)
      if((s_pos->second==value) && (s_pos->first==value))
	return true;
  }
  return false;
}

dna scheme_mutator::operator()(const dna&d,double prc)
{
  dna result(d);
  for(int i=0;i<d.size();i++){
    if(in_scheme(result[i],i))
      continue;
    if(percent()<prc)
      result[i]=int_mutate(result[i],prc);
  }
  assert(result.size()==d.size());
  return result;
}
