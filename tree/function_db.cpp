#include <stdexcept>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>

#include <boost/lexical_cast.hpp>

#include "node.hpp"
#include "function_db.hpp"
namespace Tree
{
  int FunctionDB::m_next_number=0;
  FunctionDB::FunctionDB()
  {}

  FunctionDB::~FunctionDB()
  {}
  
  int FunctionDB::add_function(FunctionNode*f)
  {
    m_functions[FunctionDB::m_next_number++]=p_BaseNode((BaseNode*)(f));
    return m_next_number-1;
  }
  
  void FunctionDB::add_variable(const std::string name)
  {
    m_variables[FunctionDB::m_next_number++]=p_BaseNode(new VarNode(name));
  }

  void FunctionDB::add_variables(int count)
  {
    for(int i=0;i<count;++i)
      m_variables[FunctionDB::m_next_number++]=p_BaseNode(new VarNode("x-"+boost::lexical_cast<std::string>(i)));
  }

  int FunctionDB::add_constant(const TermType&tt)
  {
    m_constants[FunctionDB::m_next_number++]=p_BaseNode(new ConstNode(tt));
    return FunctionDB::m_next_number-1;
  }
  
  p_BaseNode FunctionDB::operator[](int index)
  {
    node_map::const_iterator pos=m_functions.find(index);
    if(pos!=m_functions.end())
      return pos->second;

    pos=m_constants.find(index);
    if(pos!=m_constants.end())
      return pos->second;

    pos=m_variables.find(index);
    if(pos!=m_variables.end())
      return pos->second;

    throw std::logic_error("FunctionDB::operator[]: "+boost::lexical_cast<std::string>(index));
  }
  
  int  FunctionDB::size()const  
  {
    return m_functions.size()+m_variables.size()+m_constants.size();
  }

  ivector FunctionDB::functions()const  // Номера для функций
  {
    return ::keys(m_functions);
  }
  
  ivector FunctionDB::variables()const  // номера для переменных
  {
    return ::keys(m_variables);
  }
  
  ivector FunctionDB::constants()const  // Номера для констант
  {
    return ::keys(m_constants);
  }
    
  ivector FunctionDB::terms()const      // Номера для констант и переменных
  {
    ivector result;
    ivector var_keys=this->variables();
    ivector const_keys=this->constants();
    std::back_insert_iterator<ivector> to_result(result);

    std::copy(var_keys.begin(),var_keys.end(),to_result);
    std::copy(const_keys.begin(),const_keys.end(),to_result);

    return result;
  }
  
  ivector FunctionDB::keys()const       // Все имеющиеся номера
  {
    ivector result;
    ivector term_keys=this->terms();
    ivector func_keys=this->functions();
    std::back_insert_iterator<ivector> to_result(result);

    std::copy(term_keys.begin(),term_keys.end(),to_result);
    std::copy(func_keys.begin(),func_keys.end(),to_result);
    return result;
  }
  
  int FunctionDB::var_count()const      // Количество переменных
  {
    return m_variables.size();
  }
};//namespace Tree
