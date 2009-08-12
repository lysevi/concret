#include "population.hpp"
#include "selector.hpp"
#include <ga/crossover.hpp>
#include <ga/fitness.hpp>
#include <ga/mutator.hpp>
#include <ga/crossover.hpp>
#include <ga/bin_dna_generator.hpp>
#include <utils/utils.hpp>

#include "std_ga.hpp"

#include <numeric>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/timer.hpp>
#include <iostream>

using namespace boost;

std_ga::std_ga(selector*s,mutator*m,crossover*c,bin_dna_generator*g):m_s(s),
								     m_m(m),
								     m_c(c),
								     m_g(g),
								     m_name("std_ga"),
								     m_dump_enable(false),
								     m_generation_number(0),
								     m_p_number(FIRST_POPULATION),
								     m_p_first(NULL),
								     m_p_second(NULL),
								     m_p_position(0),
								     m_times(10,0),
								     m_times_index(0)
{}

std_ga::~std_ga()
{
  delete m_p_first;
  delete m_p_second;
}

void std_ga::set_params(const params&param)
{
  m_param=param;
}

void std_ga::init()
{
  // если ни одно из популяций не проинициализированна
  if(m_p_first==NULL){
    m_p_first=new population(m_param.psize);
    m_p_second=new population(m_param.psize);
    m_p_number=FIRST_POPULATION;
    m_p_position=0;
  }
  else
    if(m_p_first->size()==0){
      m_p_first->resize(m_param.psize);
      m_p_second->resize(m_param.psize);
    }
  m_g->setSize(m_f->size());
  int psize=m_param.psize;
  int sz=m_p_position;
  for(int i=sz;i<psize;i++){
    p_dna tmpD(m_g->generate());
    addIndivid(tmpD);
  }
  switch_population();
}

void std_ga::clean()
{
  m_p_first->clear();
  m_p_second->clear();
  m_cache.clear();
  m_p_position=0;
}

double std_ga::calc_ftn(const p_dna&individ)
{
  if((m_generation_number%20)==0)
    m_cache.clear();
  FtnCache::const_iterator pos=m_cache.find(individ->genom());
  if(pos!=m_cache.end()){
    return pos->second;
  }
  else{
    double f=(*m_f)(individ);
    m_cache[individ->genom()]=f;
    return f;
  }
}

void std_ga::addIndivid(const p_dna&individ)
{
  if(m_p_position>=other_population()->size()){
    return;
  }
  p_dna tmpD=individ;
  tmpD->ftn(calc_ftn(individ));
  (*other_population())[m_p_position]=tmpD;
  ++m_p_position;
  massert(tmpD->size()==individ->size());
}

family_vector std_ga::select(const population&p,int count)
{
  return m_s->select(p,count);
}

double std_ga::oneStep()
{
  family_vector fv=select(*cur_population(),static_cast<int>(cur_population()->size()*m_param.sp));
  
  BOOST_FOREACH(family fm,fv){
    p_dna father=byIndex(*(cur_population()),fm.first);
    p_dna mather=byIndex(*(cur_population()),fm.second);

    p_dna_vector dv=(*m_c)(father,mather);

    BOOST_FOREACH(p_dna d,*dv.get()){
      p_dna tmpD(d);
      addIndivid((*m_m)(tmpD,m_param.get_mpecent_for(0)));
    }
  }
  p_dna bestDna=best(*cur_population());

  if((*other_population())[0]->ftn()>bestDna->ftn())
    (*other_population())[0]=bestDna;

  init();

  m_generation_number++;
  if(m_dump_enable){
    population::const_iterator pos=cur_population()->begin();
    std::cout<<m_generation_number<<';';
    for(;pos!=cur_population()->end();++pos)
      std::cout<<(*pos)->ftn()<<';';
    std::cout<<std::endl;
  }
  return best(*cur_population())->ftn();
}


solution std_ga::getSolution(int max_steps,double min_ftn,bool verbose)
{
  boost::timer t0;      //Время выполнения в милисекундах.
  for(int i=0;i<max_steps;i++){
    t0.restart();
    double best_ftn=oneStep();
    double time=t0.elapsed();
    m_times[m_times_index%m_times.size()]=time;
    m_times_index++;
    if(verbose){
      p_dna best_dna=best(*cur_population());
      double max_dist=m_f->max_distance(best_dna);
      if(max_dist!=0.0){
	PRINT("step="<<i<<" p="<<cur_population()->size()<<" best="<<best_ftn<<", "<<max_dist
	      <<" worst="<<worst(*cur_population())->ftn()<<" time= "<<time<<" среднее="<<std::accumulate(m_times.begin(),m_times.end(),0.0)/m_times.size()
	      <<" cache="<<m_cache.size());
      }
      else{
	PRINT("step="<<i<<" p="<<cur_population()->size()<<" best="<<best_ftn
	      <<" worst="<<worst(*cur_population())->ftn()<<" time= "<<time<<" среднее="<<std::accumulate(m_times.begin(),m_times.end(),0.0)/m_times.size()
	      <<" cache="<<m_cache.size());
      }
    }

    if(best_ftn<=min_ftn)
      return make_pair(i,best(*cur_population()));
  }
  return make_pair(max_steps,best(*cur_population()));
}

void std_ga::setFitness(fitness*ftn)
{
  m_f=ftn;
  m_g->setSize(ftn->size());
}

void std_ga::enable_dump()
{
  m_dump_enable=true;
}

void std_ga::disable_dump()
{
  m_dump_enable=false;
}

population* std_ga::cur_population()
{
  if(m_p_number==FIRST_POPULATION)
    return m_p_first;
  else
    return m_p_second;
}

population* std_ga::other_population()
{
  if(m_p_number==SECOND_POPULATION)
    return m_p_first;
  else
    return m_p_second;
}

void std_ga::switch_population()
{
  if(m_p_number==FIRST_POPULATION){
    m_p_number=SECOND_POPULATION;
  }
  else{
    m_p_number=FIRST_POPULATION;
  }
  m_p_position=0; // чтобы не затирать лучшего
}
