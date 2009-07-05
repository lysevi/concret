#include "population.hpp"
#include "selector_rnd.hpp"

family_vector rnd_selector::select(const population&p,const int fcount)
{
  family_vector result(fcount);
  for(int i=0;i<fcount;i++)
    result[i]=std::make_pair(m_random.uniform(0,p.size()-1),
			     m_random.uniform(0,p.size()-1));
  return result;
}
