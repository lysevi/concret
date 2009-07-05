#ifndef _crossover_
#define _crossover_

#include "dna.hpp"
#include <vector>
#include <memory>

typedef std::vector<p_dna>           dna_vector;
typedef std::auto_ptr<dna_vector>  p_dna_vector;

class crossover
{
public:
  virtual p_dna_vector operator()(const p_dna&father,const p_dna&mather);
};
#endif
