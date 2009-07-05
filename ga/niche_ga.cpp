#include "population.hpp"
#include "selector.hpp"
#include <ga/bin_dna_generator.hpp>
#include <utils/utils.hpp>

#include "niche_ga.hpp"
#include <utils/random.hpp>
#include <utils/utils.hpp>
#include <utils/math_funcs.hpp>
#include <utility>

niche_ga::niche_ga(selector*s,mutator*m,crossover*c,bin_dna_generator*g):std_ga(s,m,c,g),
									 call_nums(0)
{
  m_name="niche_ga";
}

family_vector niche_ga::select(const population&p,int count)
{
  dna_cmeans::u_vector data=fill_data_vector(p);

  int cluster_count=static_cast<int>(p.size()*0.10);
  dna_cmeans::result r;
  if(call_nums>=10){
    call_nums=0;
    cm.m_center_sequence.erase(cm.m_center_sequence.begin(),cm.m_center_sequence.end());
  }
    
  if(cm.m_center_sequence.size()==0){
    r=cm.cluster(dna_distance,cluster_count,data.begin(),data.end(),data.size(),1.0);
  }
  else{
    r=cm.cluster(dna_distance,data.begin(),data.end(),data.size());
  }
  call_nums++;
  clusters cls=dna_cmeans::u2clsuters(r.u);

  Random rnd;
  family_vector result(count);
  int c=0; // сколько мы уже отобрали для скрещивания

  while(c!=count){
    int father_cluster=rnd.uniform(0,cls.size()-1);
    if(cls[father_cluster].size()<2)
      continue;

    int father_index=rnd.uniform(0,cls[father_cluster].size()-1);

    int mather_cluster=father_cluster;

    int mather_index=rnd.uniform(0,cls[mather_cluster].size()-1);

   
    result[c]=std::make_pair(cls[father_cluster][father_index].first,
			     cls[mather_cluster][mather_index].first);
    c++;
  }

  return result;
}
