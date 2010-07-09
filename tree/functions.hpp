#ifndef _tree_functions_hpp_
#define _tree_functions_hpp_

class FunctionDB;

namespace Tree
{
  struct FuzzyFDB
  {
    FunctionDB* fdb;
    int root_number;
    ivector second_layer;
  };
  
  FunctionDB* std_functions_db();
  FuzzyFDB* fuzzy_function_db(const dvector&y,const int x_count);
};// namespace Tree

#endif
