#ifndef _dna_hpp_
#define _dna_hpp_

#include <utils/utils.hpp>
#include <boost/shared_ptr.hpp>

const double big_double=101010101010101010.10101010101010;

class dna;

typedef boost::shared_ptr<dna> p_dna;

class dna
{
public:
  typedef ivector gvector;
  
  dna();
  explicit dna(int size);
  dna(const dna&other);
  dna(const gvector&other);
  dna& operator=(const dna&other);

  int size()const;

  int&operator[](int index);
  int operator[](int index)const;
  float get(int index)const;

  double ftn()const;
  void   ftn(double v);

  virtual bool operator<(const dna&other)const;
  virtual bool operator==(const dna&other)const;
  dna  operator*(const double v)const;
  dna& operator+=(const dna&v);
  dna  operator/(const double v);

  typedef gvector::iterator       iterator;
  typedef gvector::const_iterator const_iterator;

  iterator       begin();
  iterator       end();
  const_iterator       begin()const;
  const_iterator       end()const;
  gvector genom()const;
protected:
  gvector m_genom;
  double  m_ftn;
};


double dna_distance(dna a,dna b);
#endif
