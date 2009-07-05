#include <ga/params.hpp>
#include <utils/utils.hpp>

double params::get_mpecent_for(int i)
{
  if(mpv.size()==0)
    return mp;
  massert(i<mpv.size());
  return mpv[i];
}

params make_params(double mp,double sp,int psize)
{
  params res={dvector(),mp,sp,psize};
  return res;
}

params make_params(dvector mv,double sp,int psize)
{
  params res={mv,0.0,sp,psize};
  return res;
}
