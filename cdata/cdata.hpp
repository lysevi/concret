#ifndef _cdata_hpp_
#define _cdata_hpp_

#include <utils/utils.hpp>
#include <boost/shared_ptr.hpp>

namespace Concrete
{
  typedef boost::shared_ptr<dvector> p_component;
  class CData
  {
    typedef std::vector<p_component> dmatrix;
  public:
    CData();
    CData(const std::string&xdata_file);
    CData(const CData&other);
    void init();
    CData&operator=(const CData&other);
    int size()const;
    CData bootstrap(int percent,double delta_size);          // Увеличивает количество данных с поомощью метода bootstrap
    p_component operator[](const int index)const;
    double y_for_xp(int index)const;   // выход для опыта с номером index
    int x_count()const; // количество входных параметров
  protected:
    p_component convert_to_dvector(const std::string&s)const; // преобразует строку чисел разделенных ';' в вектор вещественных чисел
  protected:
    std::string m_xdata_file;
    
    dmatrix     m_x_matrix;
    p_component m_y_vector;
  };

  // Формирует список индексов, используемыз для обучения.
  ivector make_learn_indexes(int data_size,double percent);
};//namespace Concrete

#endif
