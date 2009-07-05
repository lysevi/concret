#ifndef _fitness_
#define _fitness_

#include "dna.hpp"
#include <utils/random.hpp>
#include <string>

class fitness
{
public:
  fitness(std::string name);
  fitness(int size,std::string name);
  std::string name()const {return m_name;};
  virtual double operator()(const p_dna&d);
  virtual int  size();
  virtual double   max_distance(const p_dna&d);
protected:
  int m_size;
  std::string m_name;
  Random m_rnd;
};
#endif
