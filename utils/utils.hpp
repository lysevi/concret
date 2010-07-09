#ifndef _utils_
#define _utils_

#include <stdexcept>
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <memory>
#include <map>
#include <boost/foreach.hpp>
#include <boost/array.hpp>

#define foreach BOOST_FOREACH

using namespace boost;
using boost::array;

typedef std::vector<int> ivector;
typedef std::vector<double> dvector;

enum FGColor
  {
    BLACK=30,
    RED=31,
    GREEN=32,
    YELLOW=33,
    BLUE=34,
    PURPLE=35,
    GRBLUE=36,
    WHITE=37
  };

#define massert(f)   if(!f) assert_msg(std::string(__FILE__),__LINE__);
#define LOGN(exp)   std::cout<<exp;std::cout.flush();

#ifdef WITH_COLORS
# define LOG(exp)    std::cout<<"\033[1m \E[32;40m"<<exp<<"\033[0m"<<std::endl;
# define LOGC(exp,fg,bg)    std::cout<<"\033[1m \E["<<bg<<";"<<fg<<"m"<<exp<<"\033[0m"<<std::endl;
#else
# define LOG(exp)         std::cout<<exp<<std::endl;
# define LOGC(exp,fg,bg)  std::cout<<exp<<std::endl;
#endif

#define PRINT(exp)  LOGC(exp,BLUE,WHITE);
#define PRINTN(exp) LOGC(exp,GREEN,WHITE); 
#define LOGD(exp)   LOGC(exp,RED,BLACK);

void assert_msg(std::string file,int line)throw(std::logic_error);

template<class T,class IteratorType>
bool in(const  IteratorType begin,const  IteratorType end,T value)
{
  return std::find(begin,end,value)!=end;
}

template<class K,class V>
bool in(const  std::map<K,V> m,const  K key)
{
  return m.find(key)!=m.end();
}


template<class T>
std::list<T>&operator<<(std::list<T>&l,T elem)
{
  l.push_back(elem);
  return l;
}

template<class T>
std::vector<T>&operator<<(std::vector<T>&l,T elem)
{
  l.push_back(elem);
  return l;
}

template<class T>
std::vector<T>&operator<<(std::vector<T>&l,std::vector<T>&r)
{
  for(int i=0; i<r.size();++i)
    l.push_back(r[i]);
  return l;
}

template<class K,class V>
std::vector<K> keys(const std::map<K,V>&m)
{
  std::vector<K> result;
  typename std::map<K,V>::const_iterator pos;
  for(pos=m.begin();pos!=m.end();++pos)
    result.push_back(pos->first);
  return result;
}

#endif
