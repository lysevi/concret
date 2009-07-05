#include "dna.hpp"
#include <utils/binary.hpp>
#include <utils/math_funcs.hpp>
#include <iostream>

dna::dna():m_genom(0),
	   m_ftn(big_double)
{}

dna::dna(int size):m_genom(size,int()),
		   m_ftn(big_double)
{
  massert(m_genom.size()==size);
}

dna::dna(const dna&other):m_genom(other.m_genom),
			  m_ftn(other.m_ftn)
{
  massert(m_genom.size()==other.size());
}

dna::dna(const gvector&other):m_genom(other)
{}

dna& dna::operator=(const dna&other)
{
  m_genom=other.m_genom;
  m_ftn=other.m_ftn;
  massert(m_genom.size()==other.size());
  return *this;
}

int dna::size()const
{return m_genom.size();}

int&dna::operator[](int index)
{
  massert((index<0)&&(index>m_genom.size()));
  return m_genom[index];
}

float dna::get(int index)const
{
  massert((index<0)&&(index>m_genom.size()));
  return bin2real(m_genom[index]);
}

int dna::operator[](int index)const
{
  massert((index<0)&&(index>m_genom.size()));
  return m_genom[index];
}

double dna::ftn()const
{return m_ftn;}

void dna::ftn(double v)
{m_ftn=v;}

bool dna::operator<(const dna&other)const
{
  if((m_ftn<other.m_ftn)&&(m_genom.size()<other.m_genom.size()))
    return true;
  else
    return false;
}

bool dna::operator==(const dna&other)const
{
  return (m_ftn==other.m_ftn)&&(m_genom.size()==other.m_genom.size());
}

dna::iterator dna::begin()
{
  return m_genom.begin();
}

dna::iterator dna::end()
{
  return m_genom.end();
}

dna::const_iterator dna::begin()const
{
  return m_genom.begin();
}

dna::const_iterator dna::end()const
{
  return m_genom.end();
}

dna::gvector dna::genom()const
{
  return m_genom;
}


double dna_distance(dna a,dna b)
{
  return distance_l1(a.begin(),a.end(),b.begin(),b.end());
}

dna dna::operator*(const double v)const
{
  dna result(m_genom.size());
  for(int i=0;i<m_genom.size();++i){
    result[i]=static_cast<int>(m_genom[i]*v);
  }
  return result;
}

dna&dna::operator+=(const dna&v)
{
  for(int i=0;i<m_genom.size();++i){
    m_genom[i]+=v[i];
  }
  return *this;
}

dna dna::operator/(const double v)
{
  dna result(m_genom.size());
  for(int i=0;i<m_genom.size();++i){
    result[i]=static_cast<int>(m_genom[i]/v);
  }
  return result;
}
