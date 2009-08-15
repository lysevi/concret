#ifndef _ga_gp_fitness_
#define _ga_gp_fitness_

#include <utils/utils.hpp>
#include <ga/fitness.hpp>
#include <cdata/cdata.hpp>
#include <tree/node.hpp>
#include <tree/tree.hpp>
#include <tree/function_db.hpp>

class GpFitness:public fitness
{
public:
  GpFitness(const double percent_to_learn,Concrete::CData*cdata,Tree::FunctionDB*fdb);
  void init();
  void clear();
  double operator()(const p_dna&d);     // среднее отклонение от выборки
  void   check_solution(const p_dna&d,Concrete::CData*cdata=NULL); // выводит максимальное и среднее отклонение от выборки
  double   max_distance(const p_dna&d); // максимальное отклонение от выборки
  void  set_numbers(const ivector&numbers);
  Tree::VarMap make_varmap(Concrete::CData*cdata,int string);
protected:
  Concrete::CData *m_cdata;
  Tree::FunctionDB*m_fdb;
  ivector          m_numbers;
  double           m_percent_to_learn;
};

#endif
