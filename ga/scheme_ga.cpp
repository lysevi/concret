#include "population.hpp"
#include "scheme_ga.hpp"
#include "schema.hpp"
#include "scheme_mutator.hpp"
#include "scheme_dna_generator.hpp"

#include <utils/io.hpp>
#include <utils/utils.hpp>
#include <algorithm>

scheme_ga::scheme_ga(selector*s,mutator*m,crossover*c,scheme_dna_generator*g,bool use_mutator):std_ga(s,m,c,g),
											       call_nums(0),
											       m_use_mutator(use_mutator)
{
  m_name="schema_ga";
}

scheme_db scheme_ga::select_schemes()
{
  const int dna_size=m_g->size();
  // Кластеризуем
  dna_cmeans::u_vector data=fill_data_vector(*cur_population());

  int cluster_count=static_cast<int>(cur_population()->size()*0.10);
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

  /*Выделяем схемы*/
  scheme_db sdb;
  for(int c_num=0;c_num<cls.size();++c_num){ //схемы ищутся только в отдельных кластерах
    if(cls[c_num].size()<2)
      continue;
    int cur_symbol=0;// Позиция в днк,которую проверяем.

    double  ftn=0; // среднее значение фитнесса для текущего кластера
    for(int i=0;i<cls[c_num].size();++i){
      ftn+=byIndex(*cur_population(),cls[c_num][i].first)->ftn();
    }
    ftn/=cls[c_num].size();

    symbol_list sch;
    for(;cur_symbol<dna_size;++cur_symbol){

      ivector values(cls[c_num].size()); // Найденные в кластере значения на cur_symbol позиции
      for(int c_pos=0;c_pos<cls[c_num].size();++c_pos){
	// Идем по кластеру
	values[c_pos]=(*byIndex(*cur_population(),cls[c_num][c_pos].first))[cur_symbol];
      }
      values.erase(unique(values.begin(),values.end()),values.end());

      if(values.size()==1){
	// Значит схема
	sch.push_back(make_pair(values[0],cur_symbol));
      }
      else
	sch.push_back(make_pair(0,-1));
    }
    schema s={sch,ftn};
    sdb<<s;
  }
  return merge_sdb(sdb);
}

void scheme_ga::init()
{
  if(cur_population()==NULL)
    return std_ga::init();

  if(cur_population()->size()==0)
    return std_ga::init();

  scheme_db sdb=select_schemes();
  scheme_dna_generator* scg=dynamic_cast<scheme_dna_generator*>(m_g);
  scg->schemes=sdb;

  if(m_use_mutator){
    scheme_mutator*sm=dynamic_cast<scheme_mutator*>(m_m);
    sm->set_scheme_db(sdb);
  }
  return std_ga::init();
}
