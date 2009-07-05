#include "function.hpp"
#include <utils/utils.hpp>
#include <utils/io.hpp>
#include <cmath>

namespace fuzzy
{
  bool cmp_coords(const coord&left,const coord&right){
    return left.first<right.first;
  }
  
  Function::Function(){
  }

  Function::Function(const Function&other):m_coords(other.m_coords)
  {}

  Function::Function(const coord_vector&coords):m_coords(coords)
  {
    sort();
  }

  Function&Function::operator=(const Function&other)
  {
    if(&other==this)
      return *this;

    m_coords.clear();
    m_coords=other.m_coords;

    return *this;
  }

  void Function::sort()
  {
    std::sort(m_coords.begin(),m_coords.end(),cmp_coords);
  }
  
  double Function::operator()(const double x)const
  {
    if(m_coords.size()<2){
      LOG("???"<<m_coords<<"???")
      throw std::logic_error("Function::operator: Function not defined.");
    }
    
    //    LOG(m_coords);
    coord left(-1,-1),right(-1,-1);
  
    // до зоны определения
    if(x<m_coords[0].first){
      if(m_coords[0].second==0) // функция возрастает
	return 0;
      else
	return 1; // функция убывает
    }

    // определяем, в каких пределах лежит x

    for(int i=0;i<m_coords.size()-1;++i){
      if(x==m_coords[i].first)
	return m_coords[i].second;
      if((x>m_coords[i].first)&&(x<m_coords[i+1].first)){
	left=m_coords[i];
	right=m_coords[i+1];
      }
    }

    if((left==right)&&(left==coord(-1,-1)))
      if(m_coords[m_coords.size()-1].second==0) // функция убывает
	return 0;
      else
	return 1; 

    //    LOG(">> "<<right<<' '<<left);
    if(right.second>left.second){
      //      LOG("HERE1");
      return (((x-left.first)*(right.second-left.second))/(right.first-left.second))+left.second;
    }
    else{
      //      LOG("HERE2");
      return ((left.second-right.second)*(right.first-x))/(right.first-left.first)+right.second;
    }    
  }


  ExpFunction::ExpFunction(double c,double q):m_c(c),m_q(q)
  {}
  
  ExpFunction::ExpFunction(const ExpFunction&other):m_c(other.m_c),m_q(other.m_q)
  {}
  
  ExpFunction& ExpFunction::operator=(const ExpFunction&other)
  {
    m_c=other.m_c;
    m_q=other.m_q;
  }
  
  double ExpFunction::operator()(const double x)const
  {
    double tmp=((x-m_c)/m_q);
    return exp(-0.5*tmp*tmp);
  }
};// namespace fuzzy
