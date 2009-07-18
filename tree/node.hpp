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
    BaseNode(const std::string _name);
    virtual NodeType    type()const=0;
    virtual TermType    eval()const;
    std::string name;
  };//BaseNode

  typedef boost::shared_ptr<BaseNode> p_BaseNode;

  class FunctionNode: public BaseNode
  {
  public:
    FunctionNode(const std::string&name,int argc_count,const FuncContainer& fc);
    NodeType    type()const {return FUNCTION_NODE;};
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
    NodeType    type()const {return CONST_NODE;};
    std::string name()const;
    TermType    eval()const;
  protected:
    TermType m_value;
  };

  class VarNode: public BaseNode
  {
  public:
    VarNode(std::string name);
    NodeType    type()const {return VAR_NODE;};
  };

  class VarFuncNode: public FunctionNode
  {
  public:
    VarFuncNode(std::string name,std::string var_name,const int argc_count,const FuncContainer& fc);
    NodeType    type()const {return VARFUNC_NODE;};
    std::string var_name();
  protected:
    std::string m_var_name;
  };

  typedef std::map<std::string,TermType> VarMap; // отображение имен переменных в их значения.
};

#endif
