#ifndef _alrgebraic_funcs_
#define _alrgebraic_funcs_

#include <tree/node.hpp>

namespace Tree
{
  namespace AlgrebraicFunctions
  {

    Tree::TermType add_f(Tree::Args args);

    Tree::TermType sub_f(Tree::Args args);

    Tree::TermType mul_f(Tree::Args args);

    Tree::TermType twice_f(Tree::Args args);

    Tree::TermType half_f(Tree::Args args);

    Tree::TermType div_func_f(Tree::Args args);

    Tree::TermType sin_f(Tree::Args args);

    Tree::TermType cos_f(Tree::Args args);

    Tree::TermType sqr_f(Tree::Args args);

    Tree::TermType exp_f(Tree::Args args);

    Tree::TermType summ_f(Tree::Args args);
  }; // namespace AlgrebraicFunctions
}; // namespace Tree
#endif
