#include <vector>
#include <map>
#include <cmath>
#include <string>

#include "node.hpp"
#include "function_db.hpp"
#include "functions.hpp"
#include "algebraic_funcs.hpp"

using namespace Tree;

namespace Tree
{

  namespace AlgrebraicFunctions
  {

    TermType add_f(Tree::Args args)
    {
      return args[0]+args[1];
    }

    TermType sub_f(Tree::Args args)
    {
      return args[0]-args[1];
    }

    TermType mul_f(Tree::Args args)
    {
      return args[0]*args[1];
    }

    TermType twice_f(Tree::Args args)
    {
      return args[0]*2;
    }

    TermType half_f(Tree::Args args)
    {
      return args[0]/2.0;
    }

    TermType div_func_f(Tree::Args args)
    {
      if (args[1]!=0)
	return args[0]/args[1];
      else
	return args[0];
    }

    TermType sin_f(Tree::Args args)
    {
      return sin(args[0]);
    }

    TermType cos_f(Tree::Args args)
    {
      return cos(args[0]);
    }

    TermType sqr_f(Tree::Args args)
    {
      return sqrt(fabs(args[0]));
    }


    TermType exp_f(Tree::Args args)
    {
      return 1/(1+exp(-(args[0]-args[1])*args[2]));
    }

    TermType summ_f(Tree::Args args)
    {
      TermType result=TermType();
      for(int i=0;i<args.size();++i)
	result+=args[i];
      return result;
    }
    TermType neg_f(Tree::Args args)
    {
      return -args[0];
    }
    Tree::TermType abs_f(Tree::Args args)
    {
      return fabs(args[0]);
    }
  }; //namespace AlgrebraicFunctions
}; // namespace Tree
