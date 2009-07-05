#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <algorithm>
#include <numeric>

#include <utils/utils.hpp>
#include <utils/vector_op.hpp>

#include "node.hpp"
#include "function_db.hpp"
#include "functions.hpp"
#include "fuzzy_funcs.hpp"

#include <boost/lexical_cast.hpp>

using namespace Tree;

namespace Tree
{
  namespace FuzzyFunctions
  {
    /*
      Данная функция необходима, поскольку FuncContainer не может быть пустым,
      вылетает с исключением, при попытке использования консруктора копирования
     */
    TermType empty_function(const Args&args)
    {
      throw std::logic_error("empty_function: данная функция не может быть вызвана.");
    }
    
    FuzzySugenoRoot::FuzzySugenoRoot(const dvector&y):FunctionNode("cugeno",y.size(),FuncContainer(empty_function)),
						      m_y(y)
    {}

    TermType FuzzySugenoRoot::eval(const Args&args)const
    {
      check_arg_count(args);
      dvector y_1(m_y);
      dvector up_mul=y_1*args;
      double up=std::accumulate(up_mul.begin(),up_mul.end(),0.0);
      double down=std::accumulate(args.begin(),args.end(),0.0);
      double out=up/down; //Выход, для текущего набора
      return out;
    }

    FuzzySugenoIf::FuzzySugenoIf(const int arg_count):FunctionNode("cugeno_if-"+boost::lexical_cast<std::string>(arg_count),
								   arg_count,
								   FuncContainer(empty_function))
    {}
    
    TermType FuzzySugenoIf::eval(const Args&args)const
    {
      check_arg_count(args);
      return *std::min_element(args.begin(),args.end());
    }

    TermType fuzzy_and(Tree::Args args)
    {
      return *std::min_element(args.begin(),args.end());
    }
    
    TermType fuzzy_or(Tree::Args args)
    {
      return *std::max_element(args.begin(),args.end());
    }
    
    TermType fuzzy_not(Tree::Args args)
    {
      return TermType(1)-args[0];
    }
  }; // namespace AlgrebraicFunctions
}; // namespace Tree
