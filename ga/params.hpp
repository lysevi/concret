#ifndef _params_
#define _params_

#include <utils/utils.hpp>

struct params
{
  dvector mpv; // вероятность мутации каждого гена
  double  mp;  // вероятность мутации
  
  double      sp; // процент отбора
  int         psize;
  double get_mpecent_for(int i);
};

params make_params(double mp,double sp,int psize);
params make_params(dvector mv,double sp,int psize);


#endif
