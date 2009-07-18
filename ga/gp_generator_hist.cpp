#include <utils/random.hpp>
#include <utils/utils.hpp>

#include "gp_generator_hist.hpp"
#include <tree/tree.hpp>
#include <tree/node.hpp>
#include <tree/function_db.hpp>

GpGeneratorHist::GpGeneratorHist(Tree::FunctionDB*fdb,int max_depth):m_fdb(fdb),
								     m_max_depth(max_depth),
								     m_functions(fdb->functions()),
								     m_terms(fdb->terms())
{}

void GpGeneratorHist::set_history(history*h)
{
  m_h=h;
}

void GpGeneratorHist::generate_sub_tree(Tree::Tree&tree,int root,int depth)
{
  if(depth==0){
    int node=m_terms[m_rnd.uniform(0,m_terms.size()-1)];
    int number=tree.add_node(node);
    tree.connect(root,number);
  }
  else{
    int fnum=m_functions[m_rnd.uniform(0,m_functions.size()-1)];
    Tree::FunctionNode*node=(Tree::FunctionNode*)((*m_fdb)[fnum].get());
    int sub_root=tree.add_node(fnum);
    tree.connect(root,sub_root);
    for(int i=0;i<node->argcount();++i)
      generate_sub_tree(tree,sub_root,depth-1);
    return;
  }
}
  
Tree::Tree GpGeneratorHist::generate_tree()
{
  Tree::Tree result;
  result.set_fdb(m_fdb);
  int root_func=m_functions[m_rnd.uniform(0,m_functions.size()-1)];
  int root_num=result.add_node(root_func);
  result.set_root(root_num);
  Tree::FunctionNode*node=(Tree::FunctionNode*)((*m_fdb)[root_func].get());
  for(int i=0;i<node->argcount();++i)
    generate_sub_tree(result,root_num,m_max_depth);
  return result;
}

p_dna GpGeneratorHist::generate()
{
  Tree::Tree rnd_tree;
  if(m_h->size()>10){
    rnd_tree=generate_tree_h();
  }
  else
    rnd_tree=generate_tree();
  ivector flat_tree=rnd_tree.flat();
  p_dna result(new dna(flat_tree));
  return result;
}


void GpGeneratorHist::generate_sub_tree_h(Tree::Tree&tree,int root,int depth,int pos)
{
  if(depth==0){
    int node=m_terms[m_rnd.uniform(0,m_terms.size()-1)];
    int number=tree.add_node(node);
    tree.connect(root,number);
    return;
  }
  history::const_iterator h_pos=m_h->begin();
  count_map cm;
  
  for(h_pos;h_pos!=m_h->end();++h_pos){
    one_step_values::const_iterator os_pos=h_pos->begin();
    for(os_pos;os_pos!=h_pos->end();++os_pos)
      cm[(*os_pos)[pos]]++;
  }
  int node_num=get_most_popular(cm);
  int number=tree.add_node(node_num);
  tree.connect(root,number);
  if(in(m_terms.begin(),m_terms.end(),node_num)){
    return;
  }
  generate_sub_tree_h(tree,number,depth-1,pos+1);
}
  
Tree::Tree GpGeneratorHist::generate_tree_h()
{
  Tree::Tree result;
  result.set_fdb(m_fdb);
  int root_func=m_functions[m_rnd.uniform(0,m_functions.size()-1)];
  int root_num=result.add_node(root_func);
  result.set_root(root_num);
  Tree::FunctionNode*node=(Tree::FunctionNode*)((*m_fdb)[root_func].get());
  for(int i=0;i<node->argcount();++i)
    generate_sub_tree_h(result,root_num,m_max_depth,i+1);
  return result;
}

int GpGeneratorHist::get_most_popular(const count_map&cm)const
{
  count_map::const_iterator pos=cm.begin();
  int max_value=-1;
  int max_index=-1;
  for(pos;pos!=cm.begin();++pos){
    if(pos->second>max_value){
      max_value=pos->second;
      max_index=pos->first;
    }
  }
  return max_index;
}
