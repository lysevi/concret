#include "bin_fitness.hpp"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <boost/lexical_cast.hpp>
#include <utils/binary.hpp>
#include <utils/vector_op.hpp>
#include <cdata/cdata.hpp>
#include <fuzzy/fuzzy_db.hpp>

bin_fitness::bin_fitness(int size):fitness(size,"diafant_"+boost::lexical_cast<std::string>(size))
{}

double bin_fitness::operator()(const p_dna&d)
{
  double res=0.0;
  for(int i=1;i<=d->size();++i){
    res+=d->get(i-1)*i;
  }
  return fabs(d->size()*d->size()-res);
}

bin_haupt1::bin_haupt1():fitness(1,"haupt1")
{}

double bin_haupt1::operator()(const p_dna&d)
{
  return fabs(1-fabs(d->get(0))+cos(d->get(0)));
}

bin_haupt2::bin_haupt2():fitness(1,"haupt2")
{}

double bin_haupt2::operator()(const p_dna&d)
{
  return fabs(0-fabs(d->get(0))+sin(d->get(0)));
}


bin_haupt3::bin_haupt3():fitness(2,"haupt3")
{}

double bin_haupt3::operator()(const p_dna&d)
{
  return fabs(d->get(0)+d->get(1));
}


bin_haupt4::bin_haupt4():fitness(2,"haupt4")
{}

double bin_haupt4::operator()(const p_dna&d)
{
  double res=100*pow((d->get(1)-pow(d->get(0),2)),2)-pow(1-d->get(0),2);
  return fabs(0-res);
}

bin_haupt5::bin_haupt5():fitness(2,"haupt5")
{}

double bin_haupt5::operator()(const p_dna&d)
{
  double res=0.0;
  for(int i=0;i<d->size();++i){
    double x=d->get(i);
    res+=fabs(x)-10*cos(sqrt(10*x));
  }
  return fabs(-10-res);
}

bin_haupt6::bin_haupt6():fitness(1,"haupt6")
{}

double bin_haupt6::operator()(const p_dna&d)
{
  double x=d->get(0);
  return fabs(-100.22-(x*x+x)*cos(x));
}

bin_haupt10::bin_haupt10():fitness(2,"haupt10")
{}

double bin_haupt10::operator()(const p_dna&d)
{
  double res=100*pow((d->get(1)-pow(d->get(0),2)),2)-pow(1-d->get(0),2);
  return fabs(0-res);
}

bin_haupt11::bin_haupt11():fitness(2,"haupt11")
{}

double bin_haupt11::operator()(const p_dna&d)
{
  double x1=d->get(0);
  double x2=d->get(1);
  double res=1+(x1*x1+x2*x2)/4000-cos(x1)*cos(x2);
  return fabs(0-res);
}

bin_rosenbrock::bin_rosenbrock(int size):fitness(size,"rosenbrock"+boost::lexical_cast<std::string>(size))
{}

double bin_rosenbrock::operator()(const p_dna&d)
{
  double result=0;
  for(int i=0;i<d->size()-1;++i){
    result+=100*pow(d->get(i+1)-pow(d->get(i),2),2)+pow(d->get(i)-1,2);
  }
  return fabs(result);
}

/*
  Длина хромосомы равна - ((Количество x)* количество экспериментов) * 3
  3 - количество параметров у экспонициальной функции активации.
 */
bin_sugeno::bin_sugeno(Concrete::CData*cdata,const ivector&numbers):fitness(cdata->x_count()*numbers.size()*3,"sugeno"),
								    m_cdata(cdata),
								    m_numbers(numbers)
{}

double bin_sugeno::operator()(const p_dna&d)
{
  fuzzy::Function*y_function=fuzzy::function3(fuzzy::coord(0,0),
					      fuzzy::coord(0.5,1.0),
					      fuzzy::coord(1.0,0));
  fuzzy::MyuFunctions mf={fuzzy::fvector(0),y_function};
  const int x_count=m_cdata->x_count();
  int i=0;
  
  for(int k=0;k<m_numbers.size();++k)
    for(int x=0;x<x_count;++x){
      fuzzy::ExpFunction*ff=new fuzzy::ExpFunction(d->get(i),d->get(i+1));
      mf.x_funcs.push_back(ff);
      i+=2;
    }
  fuzzy::rule_vector rules=fuzzy::make_rules(*m_cdata,mf,m_numbers);

  dvector errors;       // ошибка на новых данных
  for(int i=0;i<m_numbers.size();++i){

    dvector alphas(m_numbers.size());
    dvector y_1(m_numbers.size());

    // считаем выход по каждому правилу для X из текущего набора
    for(int j=0;j<rules.size();++j){
      dvector myu_x(x_count);
      for(int x=0;x<x_count;++x){
	double x_value=(*m_cdata)[m_numbers[i]]->at(x);
	myu_x[x]=rules[j](x_value,x);
      }
      alphas[i]=*std::min_element(myu_x.begin(),myu_x.end());
      y_1[i]=rules[i].y();
    }
    // Собственно вывод. Алгоритм из черной книги
    dvector up_mul=alphas*y_1;
    double up=std::accumulate(up_mul.begin(),up_mul.end(),0.0);
    double down=std::accumulate(alphas.begin(),alphas.end(),0.0);
    double etalon=m_cdata->y_for_xp(m_numbers[i]);
    double out=up/down; //Выход, для текущего набора
    double delta=fabs(out-etalon);

    errors.push_back(delta);
  }

  // Средняя ошибка.
  return std::accumulate(errors.begin(),errors.end(),0.0)/errors.size();
}
