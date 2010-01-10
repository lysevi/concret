#include <cdata/cdata.hpp>
#include <utils/random.hpp>
#include <utils/utils.hpp>
#include <utils/io.hpp>
#include <fuzzy/rule.hpp>
#include <fuzzy/fuzzy_db.hpp>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <utils/vector_op.hpp>
#include <stdio.h>
/*
  Аппроксимация с помощью вывода Сугэно 0-порядка.
  Обучается на данных из bootstrap, а тестируется на реальных данных.
*/

const int    resize_data=2; // для BOOTSTRAP
double percent_to_learn=1.0;

using fuzzy::coord;
using fuzzy::Function;
using fuzzy::function3;
using fuzzy::fvector;


int main(int argc,char*argv[])
{
  if(argc!=3){
    LOG("usage: "<<argv[0]<<" процент_данных_для_обучения data.csv");
    return -1;
  }

  Concrete::CData cdata(argv[2]);
  cdata.init();
  Concrete::CData bt_cdata=cdata.bootstrap(resize_data,0.05);
  
  sscanf(argv[1],"%lf",&percent_to_learn);

  int x_length=bt_cdata.x_count();
  LOG("Количество X: "<<x_length);

  // Создаем список случайных индексов для обучения системы
  ivector numbers=Concrete::make_learn_indexes(cdata.size(),percent_to_learn);
  
  fuzzy::MinMax minmax=fuzzy::find_min_max(bt_cdata,numbers);

  // Построение функций принадлжености
  fuzzy::MyuFunctions mf=fuzzy::make_myu_functions(bt_cdata,numbers,minmax);
  
  LOG("Количество функций для X: "<<mf.x_funcs.size());

  LOGN("Формирование базы нечетких правил...");

  fuzzy::rule_vector rules=fuzzy::make_rules(bt_cdata,mf,numbers);

  LOG(" "<<rules.size()<<" правил создано.");

  LOG("Уменьшаем количество правил...");
  rules=fuzzy::compress_fuzzy_db(bt_cdata,rules);
  LOG("Количество правил: "<<rules.size());
  
  LOG("Сугено...");

  dvector errors;       // ошибка на новых данных
  for(int i=0;i<cdata.size();++i){

    dvector alphas(cdata.size());
    dvector y_1(cdata.size());

    // считаем выход по каждому правилу для X из текущего набора
    for(int j=0;j<rules.size();++j){
      dvector myu_x(x_length);
      for(int x=0;x<x_length;++x){
	double x_value=cdata[i]->at(x);
	myu_x[x]=rules[j](x_value,x);
      }
      alphas[i]=*std::min_element(myu_x.begin(),myu_x.end());
      for(int k=0;k<resize_data;++k)
	y_1[i]=rules[i].y();
    }
    // Собственно вывод. Алгоритм из черной книги
    dvector up_mul=alphas*y_1;
    double up=std::accumulate(up_mul.begin(),up_mul.end(),0.0);
    double down=std::accumulate(alphas.begin(),alphas.end(),0.0);
    double etalon=cdata.y_for_xp(i);
    double out=0.0;
    if (down!=0.0)
      out=up/down; //Выход, для текущего набора
    double delta=fabs(out-etalon)/etalon*100.0;

    errors.push_back(delta);

    LOG("Выход для "<<i<<"-го набора данных: out="<<out
	<<" y="<<etalon
	<<" delta="<<delta);
  }

  LOG("Максимальная ошибка: "<<*std::max_element(errors.begin(),errors.end()));
  LOG("Минимальная ошибка: "<<*std::min_element(errors.begin(),errors.end()));
  LOG("Средняя ошибка: "<<std::accumulate(errors.begin(),errors.end(),0.0)/errors.size())
}
