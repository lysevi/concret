#include <vector>
#include <map>
#include <cmath>
#include <string>

#include "node.hpp"
#include "function_db.hpp"
#include "functions.hpp"
#include "algebraic_funcs.hpp"
#include "fuzzy_funcs.hpp"

using namespace Tree;


namespace Tree
{
  FunctionDB* std_functions_db()
  {
    Tree::FunctionDB* fdb=new Tree::FunctionDB;
    fdb->add_function(new Tree::FunctionNode("+",2,AlgrebraicFunctions::add_f));
    fdb->add_function(new Tree::FunctionNode("-",2,AlgrebraicFunctions::sub_f));
    fdb->add_function(new Tree::FunctionNode("*",2,AlgrebraicFunctions::mul_f));
    fdb->add_function(new Tree::FunctionNode("2*",1,AlgrebraicFunctions::twice_f));
    fdb->add_function(new Tree::FunctionNode("/2",1,AlgrebraicFunctions::half_f));
    fdb->add_function(new Tree::FunctionNode("/",2,AlgrebraicFunctions::div_func_f));
    fdb->add_function(new Tree::FunctionNode("sin",1,AlgrebraicFunctions::sin_f));
    fdb->add_function(new Tree::FunctionNode("cos",1,AlgrebraicFunctions::cos_f));
    fdb->add_function(new Tree::FunctionNode("sqr",1,AlgrebraicFunctions::sqr_f));
    fdb->add_function(new Tree::FunctionNode("exp",3,AlgrebraicFunctions::exp_f));
    fdb->add_function(new Tree::FunctionNode("summ",10,AlgrebraicFunctions::summ_f));
    fdb->add_function(new Tree::FunctionNode("neg",1,AlgrebraicFunctions::neg_f));
    fdb->add_function(new Tree::FunctionNode("abs",1,AlgrebraicFunctions::abs_f));
    return fdb;
  }

  FuzzyFDB* fuzzy_function_db(const dvector&y,const int x_count)
  {
    FuzzyFDB*result=new FuzzyFDB;
    Tree::FunctionDB* fdb=new Tree::FunctionDB;
    result->fdb=fdb;
    result->root_number=fdb->add_function(new Tree::FuzzyFunctions::FuzzySugenoRoot(y));
//     for(int i=x_count;i>=1;--i)
      result->second_layer=fdb->add_function(new Tree::FuzzyFunctions::FuzzySugenoIf(1));
    fdb->add_function(new Tree::FunctionNode("or",2,FuzzyFunctions::fuzzy_or));
    fdb->add_function(new Tree::FunctionNode("and",2,FuzzyFunctions::fuzzy_and));
    fdb->add_function(new Tree::FunctionNode("not",1,FuzzyFunctions::fuzzy_not));
    return result;
  }
};// namespace Tree
