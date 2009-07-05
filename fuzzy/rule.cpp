#include "rule.hpp"

namespace fuzzy
{
  void Rule::push_back(Function*func)
  {
    m_functions.push_back(func);
  }

  double Rule::operator()(double x,int num) // применяет функцию num к x.
  {
    return (*m_functions[num])(x);
  }

  double Rule::y()
  {
    return m_y;
  }
  
  void  Rule::set_y(double y)
  {
    m_y=y;
  }

  fvector::const_iterator Rule::begin()const
  {
    return m_functions.begin();
  }
  
  fvector::const_iterator Rule::end()const
  {
    return m_functions.end();
  }
};//namespace fuzzy
