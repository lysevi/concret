#ifndef _tree_function_db_hpp
#define _tree_function_db_hpp

#include <utils/utils.hpp>

class map;
class p_BaseNode;

namespace Tree
{
  //Класс предназначен для хранения всех функций, используемых в подборе
  class FunctionDB
  {
    typedef std::map<int,p_BaseNode> node_map;
  public:
    FunctionDB();
    ~FunctionDB();
    int add_function(FunctionNode*f);
    void add_variable(const std::string name);
    void add_variables(int count);
    int add_constant(const TermType&tt);

    p_BaseNode operator[](int index);

    int  size()const;
    
    ivector functions()const;  // Номера для функций
    ivector variables()const;  // номера для переменных
    ivector constants()const;  // Номера для констант

    ivector terms()const;      // Номера для констант и переменных
    ivector keys()const;       // Все имеющиеся номера

    int var_count()const;      // Количество переменных
  protected:
    node_map m_functions;
    node_map m_variables;
    node_map m_constants;
    static int  m_next_number;
  };
};

#endif
