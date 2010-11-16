#include <utils/random.hpp>
#include "tree.hpp"
#include "root_generator.hpp"
#include <utils/utils.hpp>

namespace Tree
{
  RootGenerator::RootGenerator(FunctionDB*fdb,int max_depth,
			       int root_function_number,ivector&second_layer_func_number):Generator(fdb,max_depth),
										      m_root_function_number(root_function_number),
										      m_second_layer_func_number(second_layer_func_number)
  {}

  int RootGenerator::get_rnd_function_number()
  {
    int fnum=m_functions[m_rnd.uniform(0,m_functions.size()-1)];
    while((fnum==m_root_function_number)          // Функция из конря и второго слоя не учавствет
	  ||(in(m_second_layer_func_number.begin(),m_second_layer_func_number.end(),fnum)))
      fnum=m_functions[m_rnd.uniform(0,m_functions.size()-1)];
    return fnum;
  }

  int RootGenerator::get_rnd_function_number_from_second_layer()
  {
    int fnum=m_rnd.uniform(0,m_second_layer_func_number.size()-1);
    return fnum;
  }

  Tree RootGenerator::generate()
  {
    Tree result;
    result.set_fdb(m_fdb);
    int root_func=m_functions[m_root_function_number];
    int root_num=result.add_node(root_func);
    result.set_root(root_num);
    FunctionNode*node=(FunctionNode*)((*m_fdb)[root_func].get());
    int sl_funcs=get_rnd_function_number_from_second_layer();
    FunctionNode*second_layer=(FunctionNode*)((*m_fdb)[m_second_layer_func_number[sl_funcs]].get());

    for(int i=0;i<node->argcount();++i){
      // Устанавливаем аргументы корня
      int sub_root=result.add_node(m_second_layer_func_number[sl_funcs]);
      result.connect(root_num,sub_root);
      // Устанавливаем аргументы второго слоя
      for(int j=0;j<second_layer->argcount();++j){
	generate_sub_tree(result,sub_root,m_max_depth-1);
      }
    }
    return result;
  }
};
