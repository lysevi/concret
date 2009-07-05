#include "binary.hpp"

#include <utility>
const int precision=100000;

union data
{
  int result;
  struct
  {
    short hi;
    short low;
  } v;
};
iipair float2iipair(float v)
{
  iipair result;
  result.first=static_cast<short int>(v);
  result.second=static_cast<short int>((v-result.first)*precision);
  return result;
}

float iipair2float(iipair v)
{
  return static_cast<float>(v.first)+static_cast<float>(v.second/static_cast<float>(precision));
}

int  short2int(short hi,short low)
{
  data d;
  d.v.hi=hi;
  d.v.low=low;
  return d.result;
}

iipair int2short(int i)
{
  data d;
  d.result=i;
  return std::make_pair(d.v.hi,d.v.low);
}

int real2bin(float g)
{
  iipair r=float2iipair(g);
  return short2int(r.first,r.second);
}

float bin2real(int g)
{
  iipair r=int2short(g);
  return iipair2float(r);
}
