#ifndef _fuzzy_db_hpp_
#define _fuzzy_db_hpp_

/*
  Содержит функции для построения базы нечетких правил.
 */

#include <fuzzy/function.hpp>
#include <fuzzy/rule.hpp>
#include <cdata/cdata.hpp>

namespace fuzzy
{

  struct MinMax
  {
    dvector max_x; //Максимальные значения X
    dvector min_x; //Минимальные значения X

    double max_y; //Максимальное значение Y
    double min_y; //Минимальное  значение Y
  };

  struct MyuFunctions
  {
    fvector  x_funcs;
    Function*y_function;
  };

  // Создает функцию, с тремя точками.
  Function*function3(const coord&_min,const coord&_av,const coord&_max);

  // Функция для поиска минимума и максимам значений, в обучающей выборке
  // cdata-данные
  // numbers-номера наборов данных, на которых нужно произвести обучение
  MinMax find_min_max(const Concrete::CData&cdata,const ivector&numbers);

  // Построение функций принадлжености
  MyuFunctions make_myu_functions(const Concrete::CData&cdata,const ivector&numbers,const MinMax&minmax);

  // Формирование базы нечетких правил...
  // См. алгоиритм в черной книге (способ 2).
  fuzzy::rule_vector make_rules(const Concrete::CData&cdata,const MyuFunctions&mf,const ivector&numbers);

  // Уменьшает количество правил в базе
  fuzzy::rule_vector compress_fuzzy_db(const Concrete::CData&cdata,const fuzzy::rule_vector&fv);
}; // namespace fuzzy



#endif
