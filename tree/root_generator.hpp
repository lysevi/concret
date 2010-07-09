#ifndef _root_generator_hpp_
#define _root_generator_hpp_

#include <tree/generator.hpp>

namespace Tree
{
  /*
    В данном генераторе можно задать номер функции,
    которая будет устанавливатья в качестве корня дерева,
    а также устанавливаются его непосредственные потомки.
    Эти функции не будут использоваться в остальных узлах дерева.
   */
  class RootGenerator:public Generator
  {
  public:
    RootGenerator(FunctionDB*fdb,int max_depth,int root_function_number,ivector &second_layer_func_number);
    int get_rnd_function_number();
    Tree::Tree generate();
  protected:
    int m_root_function_number;
    ivector m_second_layer_func_number;
  };
};
#endif
