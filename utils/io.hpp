#ifndef _utils_io_
#define _utils_io_

template<class T>
std::ostream& operator<<(std::ostream&os,const std::vector<T>&v)
{
  os<<'[';
  typename std::vector<T>::const_iterator pos=v.begin();
  while(pos!=v.end()){
    os<<*pos<<';';
    ++pos;
  }
  os<<']';
  return os;
}

template<class T>
std::ostream& operator<<(std::ostream&os,const std::list<T>&v)
{
  typename std::list<T>::const_iterator pos=v.begin();
  os<<'[';
  while(pos!=v.end()){
    os<<*pos<<';';
    ++pos;
  }
  os<<']';
  return os;
}

template<class Iterator>
void showIterator(const Iterator begin,const Iterator end,std::ostream&os=std::cout)
{
  Iterator pos=begin;
  os<<'[';
  while(pos!=end){
    os<<*pos<<';';
    ++pos;
  }
  os<<']'<<std::endl;
}

template<class T1,class T2>
std::ostream& operator<<(std::ostream&os,const std::pair<T1,T2>&v)
{
  os<<"("<<v.first<<','<<v.second<<")";
  return os;
}

template<class K,class V>
std::ostream& operator<<(std::ostream&os,const std::map<K,V>&m)
{
  typename std::map<K,V>::const_iterator pos=m.begin();
  os<<'{';
  while(pos!=m.end()){
    os<<pos->first<<':'<<pos->second<<",";
    ++pos;
  }
  os<<'}';
  return os;
}


#endif
