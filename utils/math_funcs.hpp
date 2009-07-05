#ifndef _math_funcs_
#define _math_funcs_

#include <cmath>
#include <numeric>
#include <algorithm>
#include <functional>
#include <iterator>
#include <boost/lambda/lambda.hpp>

using namespace boost::lambda;

/*
  Расстояние между последовательностями.
 */
template<class Iterator,class Iterator2>
double distance_l1(Iterator begin1,Iterator end1,Iterator2 begin2,Iterator2 end2)
{
  double result=0;
  Iterator pos1=begin1;
  Iterator2 pos2=begin2;
  for(;(pos1!=end1)&&(pos2!=end2);++pos1,++pos2)
    result+=fabs(*pos1-*pos2);
  return result;
}

template<class Iterator,class Iterator2>
double distance_max(Iterator begin1,Iterator end1,Iterator2 begin2,Iterator2 end2)
{
  double result=0;
  Iterator pos1=begin1;
  Iterator2 pos2=begin2;
  for(;(pos1!=end1)&&(pos2!=end2);++pos1,++pos2)
    result+=max(*pos1,*pos2);
  return result;
}

/*
  Сумма последовательности.
*/
template<class Iterator>
typename std::iterator_traits<Iterator>::value_type
summ(Iterator begin,Iterator end)
{
  typedef typename std::iterator_traits<Iterator>::value_type retValue;
  return std::accumulate(begin,end,retValue());
}

/*
  Сумма квадратов последовательности.
*/
template<class Iterator>
typename std::iterator_traits<Iterator>::value_type
square_summ(Iterator begin,Iterator end)
{
  typedef typename std::iterator_traits<Iterator>::value_type retValue;
  return std::accumulate(begin,end,retValue(),_1+_2*_2);
}

/*
  Нормализация последовательности.
*/
template<class Iterator>
void normalise_seq(Iterator begin,Iterator end)
{
  typedef typename std::iterator_traits<Iterator>::value_type Type;
  double s=square_summ(begin,end);
  std::transform(begin,end,begin,std::bind2nd(std::divides<Type>(),pow(s,0.5)));
}

template<class T>
T min(const T& a,const T& b)
{
  if(a<b)
    return a;
  else
    return b;
}

template<class T>
std::vector<T> min(const std::vector<T>&a,const std::vector<T>&b)
{
  if(a<b)
    return a;
  else
    return b;
}

#endif
