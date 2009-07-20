#include "population.hpp"
#include "selector.hpp"
#include <ga/crossover.hpp>
#include <ga/fitness.hpp>
#include <ga/mutator.hpp>
#include <ga/crossover.hpp>
#include <ga/bin_dna_generator.hpp>
#include <ga/selector_ch.hpp>
#include <utils/utils.hpp>

#include "afro_ga.hpp"

afro_ga::afro_ga(selector*s,mutator*m,crossover*c,bin_dna_generator*g):std_ga(s,m,c,g),
								       m_cur_chanches(-1)
{}

void afro_ga::addIndivid(const p_dna&individ)
{
  if(m_p_position>=other_population()->size()){
    return;
  }
  p_dna tmpD=individ;
  double f=(*m_f)(tmpD);
  tmpD->ftn(f);
  // ищем нужную позицию
  if(m_cur_chanches!=-1){ // Был ли сделан хоть один шаг эволюции
    int index=0;
    int min_value=m_chanches[(m_cur_chanches+1)%2][0];
    for(int i=0;i<m_param.psize-1;++i)
      if (m_chanches[(m_cur_chanches+1)%2][i]<min_value){
	min_value=m_chanches[m_cur_chanches][i];
	index=i;
      }
    (*other_population())[index]=tmpD;
    m_chanches[(m_cur_chanches+1)%2][index]=0;
  }
  else{
    (*other_population())[m_p_position]=tmpD;
    m_chanches[m_cur_chanches][m_p_position]=0;
    m_p_position++;
  }
  massert(tmpD->size()==individ->size());
}

double afro_ga::oneStep()
{
  // расчитываем среднее значение фитнесса в популяции
  double sq_fitness=0;
  for(int i=0;i<cur_population()->size();++i)
    sq_fitness+=byIndex(*cur_population(),i)->ftn();
  sq_fitness/=cur_population()->size();
  
  family_vector fv=select(*cur_population(),m_chanches[m_cur_chanches],static_cast<int>(cur_population()->size()*m_param.sp));

  BOOST_FOREACH(family fm,fv){
    p_dna father=byIndex(*(cur_population()),fm.first);
    p_dna mather=byIndex(*(cur_population()),fm.second);

    p_dna_vector dv=(*m_c)(father,mather);

    BOOST_FOREACH(p_dna d,*dv.get()){
      p_dna tmpD(d);
      double f=(*m_f)(tmpD);
      if (f<sq_fitness){
	m_chanches[m_cur_chanches][fm.first]++;
	m_chanches[m_cur_chanches][fm.second]++;
      }
      else{
	m_chanches[m_cur_chanches][fm.first]=(m_chanches[m_cur_chanches][fm.first]-1)<0?0:(m_chanches[m_cur_chanches][fm.first]-1);
	m_chanches[m_cur_chanches][fm.second]=(m_chanches[m_cur_chanches][fm.second]-1)<0?0:(m_chanches[m_cur_chanches][fm.second]-1);;
      }
      addIndivid((*m_m)(tmpD,m_param.get_mpecent_for(0)));
    }
  }
  p_dna bestDna=best(*cur_population());

  if((*other_population())[0]->ftn()>bestDna->ftn())
    (*other_population())[0]=bestDna;

  //init();
  m_generation_number++;
  if(m_dump_enable){
    population::const_iterator pos=cur_population()->begin();
    std::cout<<m_generation_number<<';';
    for(;pos!=cur_population()->end();++pos)
      std::cout<<(*pos)->ftn()<<';';
    std::cout<<std::endl;
  }
  m_cur_chanches=(m_cur_chanches+1)%2;
  return best(*cur_population())->ftn();
}

solution afro_ga::getSolution(int max_steps,double min_ftn,bool verbose)
{
  m_cur_chanches=0;
  return std_ga::getSolution(max_steps,min_ftn,verbose);
}

family_vector afro_ga::select(const population&p,const ivector&chanches,int count)
{
  return dynamic_cast<ch_selector*>(m_s)->select(p,chanches,count);
}

void afro_ga::init()
{
  m_chanches[0].resize(m_param.psize);
  m_chanches[1].resize(m_param.psize);
  std_ga::init();
}
