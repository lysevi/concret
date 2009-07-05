#ifndef _selector_rnd_
#define _selector_rnd_

#include <ga/selector.hpp>
#include <ga/population.hpp>

#include <utils/random.hpp>

class rnd_selector:public selector
{
public:
  virtual family_vector select(const population&p,const int fcount);
protected:
  Random  m_random;
};

#endif
