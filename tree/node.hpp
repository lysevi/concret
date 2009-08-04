#ifndef _tree_node_hpp_
#define _tree_node_hpp_

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

class string;
class vector;
class map;
namespace Tree
{
  enum NodeType
    {
      FUNCTION_NODE, // Узел является функцией
      CONST_NODE,    // Узел является константой
      VAR_NODE,      // Узел является переменной
      VARFUNC_NODE   // Узел является функцией, принимающей в качестве аргумента переменную по имени
    };

  typedef double                          TermType;      // Тип констант и переменных в дереве
  typedef std::vector<TermType>           Args;
  typedef boost::function<TermType(Args)> FuncContainer;

  class BaseNode
  {
  public:
    BaseNode(const std::string _name,const NodeType _type);
    TermType    eval()const;
    NodeType    type;
    std::string name;
  };//BaseNode

  typedef boost::shared_ptr<BaseNode> p_BaseNode;

  class FunctionNode: public BaseNode
  {
  public:
    FunctionNode(const std::string&name,int argc_count,const FuncContainer& fc);
    virtual TermType    eval(const Args&args)const;
    int         argcount()const {return m_argc_count;};
  protected:
    void check_arg_count(const Args&args)const throw(std::logic_error);
  protected:
    FuncContainer m_fc;
    int           m_argc_count;
  };

  class ConstNode: public BaseNode
  {
  public:
    ConstNode(TermType value);
    std::string name()const;
    TermType    eval()const;
  protected:
    TermType m_value;
  };

  class VarNode: public BaseNode
  {
  public:
    VarNode(std::string name);
  };

  class VarFuncNode: public FunctionNode
  {
  public:
    VarFuncNode(std::string name,std::string var_name,const int argc_count,const FuncContainer& fc);
    std::string var_name();
  protected:
    std::string m_var_name;
  };

  typedef std::map<std::string,TermType> VarMap; // отображение имен переменных в их значения.
};

#endif
