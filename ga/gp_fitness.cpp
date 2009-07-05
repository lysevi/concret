#include "gp_fitness.hpp"
#include <utils/utils.hpp>
#include <utils/io.hpp>
#include <utils/random.hpp>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>

GpFitness::GpFitness(const double percent_to_learn,Concrete::CData*cdata,Tree::FunctionDB*fdb):m_cdata(cdata),
											       fitness("GpFitness"),
											       m_percent_to_learn(percent_to_learn),
											       m_fdb(fdb)
{
  this->init();
}

void GpFitness::init()
{
  m_numbers=Concrete::make_learn_indexes(m_cdata->size(),m_percent_to_learn);
}

void GpFitness::clear()
{
  m_numbers.clear();
  this->init();
}

Tree::VarMap GpFitness::make_varmap(Concrete::CData*cdata)
{
  Tree::VarMap vm;
  Concrete::p_component x=(*m_cdata)[0];

  for(int k=0;k<x->size();++k)
    vm["x-"+boost::lexical_cast<std::string>(k)]=x->at(k);
  return vm;
}

void GpFitness::check_solution(const p_dna&d,Concrete::CData*cdata)
{
  if(cdata==NULL)
    cdata=m_cdata;
  LOG("numbers="<<m_numbers);
  double result=0;
  double worst_percent=0;
  //  double result_new=0;
  Tree::Tree t;
  t.set_fdb(m_fdb);
  t.flat_to_tree(d->genom());
  
  {
    std::ofstream of("gp.out");
    if(!of){
      LOG("Can`t open the file gp.out.");
      LOG(t.save_to_str());
    }
    else
      of<<t.save_to_str();
  }
  
  LOG(t.to_str());
  for(int i=0;i<m_cdata->size();++i){
    Tree::VarMap vm(make_varmap(m_cdata));


    double v=t.eval(vm);
    double y_etalon=m_cdata->y_for_xp(i);
    LOG(i<<";"<<y_etalon<<";"<<v);
    double diff=fabs(v-y_etalon)/y_etalon*100;
    result+=diff;
    if (diff>worst_percent)
      worst_percent=diff;
  }
  int size_diff=m_cdata->size()-m_numbers.size();
  if(size_diff==0)
    size_diff=1;
  LOG(result/m_cdata->size()<<", "<<worst_percent);
}

double GpFitness::operator()(const p_dna&d)
{
  double result=0;
  Tree::Tree t;
  t.set_fdb(m_fdb);
  t.flat_to_tree(d->genom());
  for(int i=0;i<m_numbers.size();++i){
    Tree::VarMap vm(make_varmap(m_cdata));

    double v=t.eval(vm);
    double etalon=m_cdata->y_for_xp(i);
    double value=fabs(v-etalon)/etalon*100.0;
    result+=value;
  }
  return result/m_numbers.size();
}

double GpFitness::max_distance(const p_dna&d)
{
  double result=0;
  double worst_percent=0;
  Tree::Tree t;
  t.set_fdb(m_fdb);
  t.flat_to_tree(d->genom());
  for(int i=0;i<m_numbers.size();++i){
    Tree::VarMap vm(make_varmap(m_cdata));

    double v=t.eval(vm);
    double etalon=m_cdata->y_for_xp(i);
    double value=fabs(v-etalon)/etalon*100.0;
    result+=value;
    if (value>worst_percent)
      worst_percent=value;
  }
  return worst_percent;
}

void  GpFitness::set_numbers(const ivector&numbers)
{
  m_numbers=numbers;
}
