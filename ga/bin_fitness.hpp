#ifndef _bin_fitness_
#define _bin_fitness_

#include "fitness.hpp"
#include <cdata/cdata.hpp>

class bin_fitness:public fitness
{
public:
  bin_fitness(int size=4);
  double operator()(const p_dna&d);
};


class bin_haupt1:public fitness
{
public:
  bin_haupt1();
  double operator()(const p_dna&d);
};

class bin_haupt2:public fitness
{
public:
  bin_haupt2();
  double operator()(const p_dna&d);
};


class bin_haupt3:public fitness
{
public:
  bin_haupt3();
  double operator()(const p_dna&d);
};

class bin_haupt4:public fitness
{
public:
  bin_haupt4();
  double operator()(const p_dna&d);
};

class bin_haupt5:public fitness
{
public:
  bin_haupt5();
  double operator()(const p_dna&d);
};

class bin_haupt6:public fitness
{
public:
  bin_haupt6();
  double operator()(const p_dna&d);
};

class bin_haupt10:public fitness
{
public:
  bin_haupt10();
  double operator()(const p_dna&d);
};

class bin_haupt11:public fitness
{
public:
  bin_haupt11();
  double operator()(const p_dna&d);
};

class bin_rosenbrock:public fitness
{
public:
  bin_rosenbrock(int size);
  double operator()(const p_dna&d);
};


class bin_sugeno:public fitness
{
public:
  bin_sugeno(Concrete::CData*cdata,const ivector&numbers);
  double operator()(const p_dna&d);
protected:
  ivector m_numbers;
  Concrete::CData*m_cdata;
};

#endif
