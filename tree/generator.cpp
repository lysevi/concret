#include <utils/random.hpp>
#include "tree.hpp"
#include "generator.hpp"
#include <utils/utils.hpp>

namespace Tree
{
  Generator::Generator(FunctionDB*fdb,int max_depth,bool fly_mode):m_max_depth(max_depth),
								   m_fly_mode(fly_mode)
  {
    m_fdb=fdb;
    m_functions=fdb->functions();
    m_terms=fdb->terms();
  }

  int Generator::get_rnd_function_number()
  {
    int fnum=m_functions[m_rnd.uniform(0,m_functions.size()-1)];
    return fnum;
  }
  
  void Generator::generate_sub_tree(Tree&tree,int root,int depth)
  {
    // @todo: Вылетает с ошибкой, когда генерирует перед эти функцию и глубина становится 0.
    if(depth==0){
      int node=m_terms[m_rnd.uniform(0,m_terms.size()-1)];
      int number=tree.add_node(node);
      tree.connect(root,number);
      return;
    }
    else{
      int fnum=get_rnd_function_number();
      BaseNode*bn=(*m_fdb)[fnum].get();
      NodeType nt=bn->type();
      switch(nt){
      case(FUNCTION_NODE):{
	FunctionNode*node=dynamic_cast<FunctionNode*>(bn);
	int sub_root=tree.add_node(fnum);
	tree.connect(root,sub_root);
	for(int i=0;i<node->argcount();++i)
	  generate_sub_tree(tree,sub_root,depth-1);
	return;
      }
      case(VARFUNC_NODE):{
	int sub_root=tree.add_node(fnum);
	tree.connect(root,sub_root);
	return;
      }
      default:{
	throw std::logic_error("Generator::generate_sub_tree: strange node type.");
      }
      }
    }
  }
  
  Tree Generator::generate()
  {
    Tree result;
    result.set_fdb(m_fdb);
    int root_func=m_functions[m_rnd.uniform(0,m_functions.size()-1)];
    int root_num=result.add_node(root_func);
    result.set_root(root_num);
    FunctionNode*node=dynamic_cast<FunctionNode*>((*m_fdb)[root_func].get());
    int depth;
    if(m_fly_mode)
      depth=m_rnd.uniform(1,m_max_depth);
    else
      depth=m_max_depth;
    for(int i=0;i<node->argcount();++i)
      generate_sub_tree(result,root_num,depth);
    return result;
  }
};// namespace Tree
