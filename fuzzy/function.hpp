#ifndef _function_
#define _function_

#include <utility>
#include <vector>

namespace fuzzy
{
  typedef std::pair<double,double> coord;
  typedef std::vector<coord>       coord_vector;
  // Класс для хранения кусочно линейной функции
  class Function{
  public:
    Function();
    Function(const Function&other);
    Function(const coord_vector&coords);
    virtual Function& operator=(const Function&other);
    virtual double operator()(const double x)const;
  protected:
    void sort();
  protected:
    coord_vector m_coords;
  };
  
  typedef std::vector<Function*> fvector;

  class ExpFunction:virtual public Function
  {
  public:
    ExpFunction(double c,double q);
    ExpFunction(const ExpFunction&other);
    ExpFunction& operator=(const ExpFunction&other);
    double operator()(const double x)const;
  protected:
    double m_c,m_q;
  };
};

#endif
