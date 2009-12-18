#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <iostream>

#include <utils/utils.hpp>
#include <utils/io.hpp>
#include "tree.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

namespace Tree
{
  int Tree::node_number=0;

  Tree::Tree():m_fdb(NULL),
	       m_root(-1)
  {}

  Tree::Tree(const Tree&other):m_fdb(other.m_fdb)
  {
    NodeMap nmap; // старый номер -> новый номер
    for(NodeMap::const_iterator pos=other.m_nodes.begin();pos!=other.m_nodes.end();++pos)
      nmap[pos->first]=add_node(pos->second);

    for(int i=0;i<other.m_edges.size();++i)
      connect(nmap[other.m_edges[i].first],nmap[other.m_edges[i].second]);
    set_root(nmap[other.m_root]);
  }

  Tree&Tree::operator=(const Tree&other)
  {
    if(&other==this)
      return *this;
    m_fdb=other.m_fdb;
    NodeMap nmap; // старый номер -> новый номер
    for(NodeMap::const_iterator pos=other.m_nodes.begin();pos!=other.m_nodes.end();++pos)
      nmap[pos->first]=add_node(pos->second);

    for(int i=0;i<m_edges.size();++i)
      connect(nmap[other.m_edges[i].first],nmap[other.m_edges[i].second]);
    set_root(nmap[other.m_root]);
    return *this;
  }

  Tree::Tree(FunctionDB*fdb,const ivector&iv):m_fdb(fdb)
  {
    flat_to_tree(iv);
  }

  Tree::~Tree()
  {}
  
  void Tree::set_fdb(FunctionDB*fdb)
  {
    m_fdb=fdb;
  }
  
  ivector Tree::numbers()const //Возвращает номера всех узлов
  {
    return keys(m_nodes);
  }

  ivector Tree::nodes()const   // Возвращает номера всех функций.
  {
    ivector result(m_nodes.size());
    NodeMap::const_iterator pos=m_nodes.begin();
    int i=0;
    for(pos;pos!=m_nodes.end();++pos,++i)
      result[i]=pos->second;
    return result;
  }
  
  int     Tree::root()const
  {
    return m_root;
  }
  
  void    Tree::set_root(int root)
  {
    m_root=root;
  }

  int     Tree::add_node(int n)          // Добавляет узел и возвращает его номер
  {
    m_nodes[Tree::node_number]=n;
    return Tree::node_number++;
  }
  
  void    Tree::connect(int from,int to) // Устанавливает соедниения для двух узлов
  {
    if(std::find(m_edges.begin(),m_edges.end(),std::make_pair(from,to))!=m_edges.end())
      return;

    if(m_nodes.find(from)==m_nodes.end())
      throw std::logic_error("Tree::connect: bad from number. "+boost::lexical_cast<std::string>(from));

    if(m_nodes.find(to)==m_nodes.end())
      throw std::logic_error("Tree::connect: bad to number. "+boost::lexical_cast<std::string>(to));

    m_edges.push_back(std::make_pair(from,to));
  }

  ivector Tree::childs_of(int n)const             // Возвращает потомков для узла с номером num
  {
    ivector result;
    for(int i=0;i<m_edges.size();++i)
      if(m_edges.at(i).first==n)
	result.push_back(m_edges.at(i).second);
    return result;
  }
  
  int Tree::parent_of(int n)const             // Возвращает предка для узла с номером num
  {
    for(int i=0;i<m_edges.size();++i)
      if(m_edges.at(i).second==n)
	return m_edges.at(i).first;
    return -1;    
  }

  TermType Tree::eval_node(int index,const VarMap&var_values) // Вычисляет значения для узла с номером index в зависимости от его типа
  {
    int num=m_nodes[index];
    p_BaseNode node=(*m_fdb)[num];

    NodeType nt=node->type;

    switch(nt)
      {
      case(CONST_NODE):{return ((ConstNode*)node.get())->eval();};

      case(VAR_NODE):{
	VarMap::const_iterator pos=var_values.find(node->name);
	if(pos==var_values.end()){
	  LOG(var_values);
	  throw std::logic_error("Tree::eval_node(VAR_NODE): bad variable name. "+node->name);
	}
	else
	  return pos->second;};

      case(FUNCTION_NODE):{
	ivector childs=this->childs_of(index);
	Args args(childs.size());
	for(int i=0;i<childs.size();++i){
	  int c=childs[i];
	  int term_number=this->m_nodes[c];
	  args[i]=this->eval_node(c,var_values);
	}
	FunctionNode*fn=(FunctionNode*)(node.get());
	return fn->eval(args);
      };
	
      case(VARFUNC_NODE):{
	VarFuncNode*vfn=(VarFuncNode*)(node.get());
	VarMap::const_iterator pos=var_values.find(vfn->var_name());
	if(pos==var_values.end()){
	  LOG(var_values);
	  throw std::logic_error("Tree::eval_node(VARFUNC_NODE): bad variable name. "+vfn->var_name());
	}
	TermType value=pos->second;
	Args args(1);
	args[0]=value;
	return vfn->eval(args);
      };
      default:{ throw std::logic_error("Tree::eval_node: bad type.");}
      };
  }
  
  TermType Tree::eval(const VarMap&var_values)                // Вычисляет выражение, которое описывается данным деревом
  {
    return this->eval_node(this->m_root,var_values);
  }
  
  ivector  Tree::flat()const // Преобразует дерево в список
  {
    ivector result;
    result.push_back(m_root);
    for(int i=0;i<m_edges.size();++i){
      result.push_back(m_edges[i].first);
      result.push_back(m_edges[i].second);
    }
    result.push_back(-1); // маркер конца списка ребер
    for(NodeMap::const_iterator pos=m_nodes.begin();pos!=m_nodes.end();++pos){
      result.push_back(pos->first);
      result.push_back(pos->second);
    }
    return result;
  }

  void     Tree::flat_to_tree(const ivector&iv) // Преобразует вектор в дерево
  {
    ivector::const_iterator sep=std::find(iv.begin(),iv.end(),-1); // граница разделения
    int seek=1;
    ivector edges(iv.begin()+1,sep);
    ivector nodes(sep+1,iv.end());

    int k=seek;
    NodeMap nmap; // старый номер -> новый номер
    for(int i=0;i<edges.size();i+=2){
      int from=-1;
      int to=-1;

      if(nmap.find(edges[i])!=nmap.end())
	from=nmap[edges[i]];
      else{
	nmap[edges[i]]=Tree::node_number+k;
	from=node_number+k;
	k+=1;
      }
      if(nmap.find(edges[i+1])!=nmap.end())
	to=nmap[edges[i+1]];
      else{
	nmap[edges[i+1]]=Tree::node_number+k;
	to=Tree::node_number+k;
	k+=1;
      }
      m_edges.push_back(std::make_pair(from,to));
    }

    for(int i=0;i<nodes.size();i+=2)
      m_nodes[nmap[nodes[i]]]=nodes[i+1];
    m_root=nmap[iv[0]];
  }

  Tree     Tree::clone()const           // Возвращает копию текущего дерева
  {
    return sub_tree(m_root);
  }

  ivector Tree::nodes_in_subtree(int parent)const //Возврыщает список узлов, которые входят в поддерево,с вершиной в parent
  {
    ivector result;
    ivector childs=childs_of(parent);
    for(int i=0;i<childs.size();++i){
      int c=childs[i];
      result.push_back(c);
      ivector sub_result=nodes_in_subtree(c);
      std::back_insert_iterator<ivector> to_result(result);
      std::copy(sub_result.begin(),sub_result.end(),to_result);
    }
    return result;
  }

  Tree     Tree::sub_tree(int num)const // Возвращает поддерево, корнем которого является index
  {
    Tree result;
    result.set_fdb(m_fdb);
    ivector sub_nodes=nodes_in_subtree(num);
    NodeMap nmap; // старый номер -> новый номер
    sub_nodes.push_back(num);

    for(int i=0;i<sub_nodes.size();++i){
      int n=sub_nodes[i];
      int node=m_nodes.find(n)->second;
      nmap[n]=result.add_node(node);
    }
    for(int i=0;i<sub_nodes.size();++i){
      int n=sub_nodes[i];
      ivector childs=childs_of(n);
      for(int j=0;j<childs.size();++j){
	int c=childs[j];
	result.connect(nmap[n],nmap[c]);
      }
    }
    NodeMap::const_iterator pos=nmap.find(num);
    result.set_root(pos->second);
    return result;
  }

  void     Tree::set_sub_tree(int parent,const Tree&tree) // Устанавливает узлу parent поддерево tree
  {
    p_BaseNode node=(*m_fdb)[m_nodes[parent]];
    int sub_root=-1;

    sub_root=parent_of(parent);
    remove_node(parent);
   
    NodeMap nmap; // старый номер -> новый номер
    for(NodeMap::const_iterator pos=tree.m_nodes.begin();pos!=tree.m_nodes.end();++pos)
      nmap[pos->first]=add_node(pos->second);

    for(int i=0;i<tree.m_edges.size();++i)
      connect(nmap[tree.m_edges[i].first],nmap[tree.m_edges[i].second]);

    if (sub_root!=-1)
      connect(sub_root,nmap[tree.root()]);
    else// мы заменили корень
      m_root=nmap[tree.root()];
  }

  // @todo: Должен возвращать глубину, а не количество узлов
  int      Tree::size()const // Количество улов в дереве
  {
    return m_nodes.size();
  }
    
  void     Tree::remove_node(int pos) //Удаляет узел, с номером pos
  {
    if(m_nodes.find(pos)==m_nodes.end())
      return;

    ivector childs=childs_of(pos);
    while(true){
      bool deleted=false; // Удаляли ли мы что-то в этой итерации цикла
      for(Edges::const_iterator i=m_edges.begin();i!=m_edges.end();++i){
	if(i->first==pos){
	  m_edges.erase(std::remove(m_edges.begin(),m_edges.end(),*i),m_edges.end());
	  deleted=true;
	  break;
	}
	if(i->second==pos){
	  m_edges.erase(std::remove(m_edges.begin(),m_edges.end(),*i),m_edges.end());
	  deleted=true;
	  break;
	}
      }
      if(!deleted)
	break;
    }
    m_nodes.erase(pos);
    for(int i=0;i<childs.size();++i){
      int c=childs[i];
      remove_node(c);
    }
    m_nodes.erase(pos);
    if (pos==m_root)
      m_root=-1;
  }

  std::string Tree::to_str(int pos)const   // Преобразует рекурсивно в строку узел с номером index и его потомков.
  {
    int num=m_nodes.find(pos)->second;
    p_BaseNode node=(*m_fdb)[num];

    NodeType nt=node->type;

    switch(nt)
      {
      case(CONST_NODE):{return boost::lexical_cast<std::string>(node->eval());};
	
      case(VAR_NODE):{
	return node->name;};
	
      case(FUNCTION_NODE):{
	std::string result="("+node->name;
	ivector childs=this->childs_of(pos);
	for(int i=0;i<childs.size();++i){
	  int c=childs[i];
	  result+=' '+this->to_str(c);
	}
	return result+')';
      };
      case(VARFUNC_NODE):{
	VarFuncNode*vfn=(VarFuncNode*)(node.get());
	std::string var_name=vfn->var_name();
	return "["+vfn->name+' '+var_name+']';
      };
      default:{ throw std::logic_error("Tree::eval_node: bad type.");}
      };
  }

  std::string Tree::to_str()const
  {
    return to_str(m_root);
  }

  void Tree::clear()           // Удаляет все узлы и связи из дерева
  {
    m_edges.clear();
    m_nodes.clear();
    m_root=-1;
  }

  std::string Tree::save_to_str()const // Преобразует из строки
  {
    std::ostringstream os;
    ivector iv=flat();
    for(int i=0;i<iv.size();++i)
      os<<iv[i]<<';';
    return os.str();
  }
  
  void Tree::restore_from_str(const std::string&s) // Преобразует из строки
  {
    typedef std::vector< std::string > split_vector_type;
    split_vector_type words;
    boost::split(words,s, boost::is_any_of(";"));

    ivector iv;

    for(int i=0;i<words.size();++i){
      try{
	boost::trim(words[i]);
	if(words[i].size()==0)
	  continue;
	iv.push_back(boost::lexical_cast<int>(words[i]));
      }
      catch(...){
	LOG("Tree::restore_from_str: Error when cast: |"<<words[i]<<'|');
      }
    }
    clear();
    flat_to_tree(iv);
  }

  int Tree::get_node_by_number(const int number)const // Возвращает номер узла по его номеру в дереве
  {
    NodeMap::const_iterator result=m_nodes.find(number);

    if(result==m_nodes.end())
      throw std::logic_error("Tree::get_node_by_number: bad number. "+boost::lexical_cast<std::string>(number));

    return result->second;
  }
};//namespace Tree
