#ifndef _selector_
#define _selector_

#include <vector>
#include <utility>

typedef std::pair<int,int>  family;
typedef std::vector<family> family_vector;

class selector
{
public:
  virtual family_vector select(const population&p,const int fcount)=0;
};
#endif
