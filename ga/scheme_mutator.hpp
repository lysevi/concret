#ifndef _scheme_mutator_
#define _scheme_mutator_

#include <ga/bin_mutator.hpp>
#include <ga/schema.hpp>

class scheme_mutator:virtual public bin_mutator
{
public:
  scheme_mutator(int bit_count);
  dna operator()(const dna&d,double percent);
  void set_scheme_db(const scheme_db&sdb);
  bool in_scheme(int value,int pos)const;
protected:
  scheme_db m_sdb;
};
#endif
