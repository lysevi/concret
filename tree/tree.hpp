#ifndef _tree_tree_hpp_
#define _tree_tree_hpp_

#include <utils/utils.hpp>
#include <utility>
#include <vector>
#include <map>

#include <tree/node.hpp>
#include <tree/function_db.hpp>

class FunctionDB;

namespace Tree
{
  typedef std::pair<int,int> Edge;
  typedef std::vector<Edge>  Edges;
  typedef std::map<int,int>  NodeMap;

  class Tree
  {
  public:
    Tree();
    Tree(FunctionDB*fdb,const ivector&iv);
    Tree(const Tree&other);
    ~Tree();
    Tree&operator=(const Tree&other);
    void set_fdb(FunctionDB*fdb);

    ivector numbers()const; //Возвращает номера всех узлов
    ivector nodes()const;   // Возвращает номера всех функций.

    int     root()const;
    void    set_root(int root);

    int     add_node(int n);          // Добавляет узел и возвращает его номер
    void    connect(int from,int to); // Устанавливает соедниения для двух узлов

    ivector childs_of(int n)const;             // Возвращает потомков для узла с номером num
    int     parent_of(int n)const;             // Возвращает предка для узла с номером num

    TermType eval(const VarMap&var_values);                // Вычисляет выражение, которое описывается данным деревом
    ivector  flat()const; // Преобразует дерево в список

    void flat_to_tree(const ivector&iv); // Преобразует вектор в дерево

    Tree     clone()const;           // Возвращает копию текущего дерева
    Tree     sub_tree(int num)const; // Возвращает поддерево, корнем которого является index

    void     set_sub_tree(int parent,const Tree&tree); // Устанавливает узлу parent поддерево tree

    int      size()const; // Количество улов в дереве
    
    void     remove_node(int pos); //Удаляет узел, с номером pos

    std::string to_str()const;          // Преобразует в строку
    
    void        clear();           // Удаляет все узлы и связи из дерева

    std::string save_to_str()const; // Преобразует из строки
    void        restore_from_str(const std::string&s); // Преобразует из строки

    void compress_const_expr(); // Заменяеет константные выражения на их значения (+ 1 2)->(3)
    int get_node_by_number(const int number)const; // Возвращает номер узла по его номеру в дереве
  protected:
    TermType eval_node(int index,const VarMap&var_values); // Вычисляет значения для узла с номером index в зависимости от его типа
    std::string to_str(int pos)const;   // Преобразует рекурсивно в строку узел с номером index и его потомков.
    ivector nodes_in_subtree(int parent)const;//Возврыщает список узлов, которые входят в поддерево,с вершиной в parent
    char expr_type(int root)const; // возращает 1 если в поддереве с корнем root все выражения константны, -1 если выражение константа, 0 если выражение не константа.
  protected:
    FunctionDB*m_fdb;
    Edges      m_edges;
    NodeMap    m_nodes;
    int        m_root;
    static int node_number;
    
  };
};//namespace Tree

#endif
