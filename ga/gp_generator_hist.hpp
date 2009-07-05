#ifndef _ga_gp_generator_hist_
#define _ga_gp_generator_hist_

#include <utils/random.hpp>
#include <tree/tree.hpp>
#include <tree/generator.hpp>

#include "history.hpp"
#include <ga/gp_generator.hpp>

#include <map>

typedef std::map<int,int> count_map; // отображение номера узла в его количество


class FunctionDB;
class Random;

class GpGeneratorHist:public bin_dna_generator
{
public:
  GpGeneratorHist(Tree::FunctionDB*fdb,int max_depth);
  p_dna generate();
  void set_history(history*h);
  void generate_sub_tree(Tree::Tree&tree,int root,int depth);
  Tree::Tree generate_tree();
  void generate_sub_tree_h(Tree::Tree&tree,int root,int depth,int pos); // с историей
  Tree::Tree generate_tree_h(); // с историей
  int get_most_popular(const count_map&cm)const; // Возвращает самый популярный узел (По встречаемости)
protected:
  history *m_h;
protected:
  Random     m_rnd;
  Tree::FunctionDB*m_fdb;
  int        m_max_depth;
  ivector    m_functions;
  ivector    m_terms;
};

#endif
