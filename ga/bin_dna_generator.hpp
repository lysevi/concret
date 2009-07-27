#ifndef _bin_dna_generator_
#define _bin_dna_generator_

#include <ga/dna.hpp>
#include <utils/random.hpp>

class bin_dna_generator
{
public:
  bin_dna_generator();
  bin_dna_generator(float from,float to,int size=1);
  int size()const;
  void setSize(int s);
  void setFrom(float f);
  void setTo(float t);
  virtual p_dna generate();
protected:
  float m_from;
  float m_to;
  int   m_size;
  Random m_rnd;
};

#endif
