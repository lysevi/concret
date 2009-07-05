#ifndef _niche_selector_
#define _niche_selector_

#include "selector_rnd.hpp"

class niche_selector:public rnd_selector
{
public:
  family_vector select(const population&p,const int fcount);
};

#endif
