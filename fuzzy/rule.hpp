#ifndef _rule_hpp_
#define _rule_hpp_

#include <fuzzy/function.hpp>

namespace fuzzy
{
  class Rule
  {
  public:
    void push_back(Function*func);
    double operator()(double x,int num); // применяет функцию num к x.
    double y();
    void  set_y(double y);
    fvector::const_iterator begin()const;
    fvector::const_iterator end()const;
  protected:
    fvector     m_functions;
    double      m_y;
  };

  typedef std::vector<Rule> rule_vector;
};//namespace fuzzy

#endif
