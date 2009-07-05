#include "niche.hpp"

data_vector fill_data_vector(const population&p)
{
  data_vector result(p.size());
  for(int i=0;i<p.size();++i)
    result[i]=byIndex(p,i)->genom();
  return result;
}
