#ifndef _binary_hpp_
#define _binary_hpp_

#include <memory>

typedef std::pair<short int,short int> iipair;

iipair float2iipair(float v);
float  iipair2float(iipair v);
int    short2int(short hi,short low);
iipair    int2short(int i);
int real2bin(float g);
float bin2real(int g);
#endif
