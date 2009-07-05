#ifndef _fuzzy_funcs_
#define _fuzzy_funcs_

#include <tree/node.hpp>
#include <fuzzy/function.hpp>

namespace Tree
{
  namespace FuzzyFunctions
  {
    class FuzzySugenoRoot:public Tree::FunctionNode
    {
    public:
      FuzzySugenoRoot(const dvector&y);
      TermType eval(const Args&args)const;
    protected:
      dvector m_y;
    };

    class FuzzySugenoIf:public Tree::FunctionNode
    {
    public:
      FuzzySugenoIf(const int arg_count);
      TermType eval(const Args&args)const;
    };

    TermType fuzzy_and(Tree::Args args);
    TermType fuzzy_or(Tree::Args args);
    TermType fuzzy_not(Tree::Args args);
  }; // namespace AlgrebraicFunctions
}; // namespace Tree

#endif
