#ifndef _mutator_
#define _mutator_

#include <ga/dna.hpp>
#include <ga/params.hpp>

class Random;

class mutator
{
public:
  mutator();
  ~mutator();
  virtual p_dna operator()(const p_dna&d,double percent);
  double percent();
protected:
  Random*m_r;
};

#endif
