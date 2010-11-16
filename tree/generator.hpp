#ifndef _tree_generator_hpp_
#define _tree_generator_hpp_

class FunctionDB;
class Random;

namespace Tree
{
  class Generator
  {
  public:
    Generator(FunctionDB*fdb,int max_depth,bool fly_mode=false);
    virtual int get_rnd_function_number();
    virtual Tree generate();
  protected:
    void generate_sub_tree(Tree&tree,int root,int depth);
  protected:
    bool       m_fly_mode; // Включен ли плавающий режим. В нем будут генерироваться деревья глубиной от 1 до m_max_depth
    Random     m_rnd;
    FunctionDB*m_fdb;
    int        m_max_depth;
    ivector    m_functions;
    ivector    m_terms;
  };
};

#endif
