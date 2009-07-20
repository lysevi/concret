#ifndef _selector_ch_
#define _selector_ch_

#include <ga/selector.hpp>
#include <ga/population.hpp>

#include <utils/random.hpp>

/*
  Производит выборку исходя из вектора шансов на скрещивание.
 */

class ch_selector:public selector
{
public:
  family_vector select(const population&p,const int fcount);
  virtual family_vector select(const population&p,const ivector&chanches,const int fcount);
protected:
  Random  m_random;
};

#endif
