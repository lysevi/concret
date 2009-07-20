#include "population.hpp"
#include "selector_ch.hpp"

#include <stdexcept>

family_vector ch_selector::select(const population&p,const int fcount)
{
  throw std::logic_error("ch_selector::select(const population&p,const int fcount) can`t be called.");
}

family_vector ch_selector::select(const population&p,const ivector&chanches,const int fcount)
{
  family_vector result(fcount);
  ivector indexes;
  for(int i=0;i<chanches.size();++i)
    for(int j=0;j<chanches[i]+1;++j) // +1 на случай, если все шансы равны 0
      indexes.push_back(i);
  
  for(int i=0;i<fcount;i++)
    result[i]=std::make_pair(indexes[m_random.uniform(0,indexes.size()-1)],
			     indexes[m_random.uniform(0,indexes.size()-1)]);
  return result;
}
