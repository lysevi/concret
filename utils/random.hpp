#ifndef _random_
#define _random_

#include <algorithm>
#include <vector>

class Random
{
public:
  Random();
  int   uniform(int from,int to)const;
  double uniform(double from,double to)const;
};


template<class T>
void shuffle(std::vector<T>&v)
{
  Random rnd;
  for(int i=0;i<v.size();++i){
    int new_index=rnd.uniform(0,v.size()-1);
    std::swap(v[i],v[new_index]);
  }
}
#endif
