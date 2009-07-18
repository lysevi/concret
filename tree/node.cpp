#include <stdexcept>
#include <vector>
#include <map>

#include <boost/lexical_cast.hpp>
#include <boost/function.hpp>

#include "node.hpp"

namespace Tree
{
  BaseNode::BaseNode(const std::string _name,const NodeType _type):name(_name),
								   type(_type)
  {}
  
  TermType    BaseNode::eval()const
  {
    throw std::logic_error("BaseNode::name not implemented");
  }
  
  FunctionNode::FunctionNode(const std::string&name,int argc_count,const FuncContainer& fc):BaseNode(name,FUNCTION_NODE),
											    m_fc(fc),
											    m_argc_count(argc_count)
  {}

  void FunctionNode::check_arg_count(const Args&args)const throw(std::logic_error)
  {
    if(args.size()!=m_argc_count)
      throw std::logic_error("FunctionNode::check_arg_count: Length error. "+name+' '
			     +boost::lexical_cast<std::string>(m_argc_count)
			     +" "
			     +boost::lexical_cast<std::string>(args.size()));    
  }

  TermType FunctionNode::eval(const Args&args)const
  {
    check_arg_count(args);
    return m_fc(args);
  }

  ConstNode::ConstNode(TermType value):BaseNode(boost::lexical_cast<std::string>(m_value),CONST_NODE),
				       m_value(value)
  {}
  
  TermType    ConstNode::eval()const
  {
    return m_value;
  }

  VarNode::VarNode(std::string name):BaseNode(name,VAR_NODE)
  {};

  VarFuncNode::VarFuncNode(std::string name,std::string var_name,const int argc_count,const FuncContainer& fc):FunctionNode(name,argc_count,fc),
													       m_var_name(var_name)
  {
    type=VARFUNC_NODE;
  }
  
  std::string VarFuncNode::var_name()
  {return m_var_name;}
};//namespace Tree
