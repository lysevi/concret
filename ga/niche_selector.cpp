#include "dna.hpp"
#include "population.hpp"

#include "niche_selector.hpp"
#include <utils/math_funcs.hpp>
#include <utils/random.hpp>

family_vector niche_selector::select(const population&p,const int fcount)
{
  Random rnd;
  family_vector result(fcount);
  int cur=0;
  int first_index=indexOfBest(p);
  p_dna d1=best(p);
  for(int i=0;i<fcount;i++){
    

    d1=byIndex(p,first_index);
    int    d2_index=(i+1)%p.size();
    p_dna d2=byIndex(p,d2_index);
    double last_distance=distance_l1(d1->begin(),d1->end(),d2->begin(),d2->end());
    
    for(int j=0;j<p.size();j++){
      if(j==first_index)
	continue;
      
      p_dna od=byIndex(p,j);
      double cur_distance=distance_l1(d1->begin(),d1->end(),od->begin(),od->end());
      if(cur_distance>last_distance){
	d2=byIndex(p,j);
	last_distance=cur_distance;
	d2_index=j;
      }
    }
    result[cur]=std::make_pair(i,d2_index);
    cur++;
    first_index=rnd.uniform(0,p.size()-1);
    p_dna d1=byIndex(p,first_index);
  }
  return result;
}
