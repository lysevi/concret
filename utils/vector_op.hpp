#ifndef _vector_op_
#define _vector_op_


template<class T>
std::vector<T> operator*(const std::vector<T>&v,double t)
{
  std::vector<T> result(v.size());
  for(int i=0;i<v.size();++i)
    result[i]=static_cast<T>(v[i]*t);
  return result;
}

template<class T>
std::vector<T> operator*(std::vector<T>&v,const std::vector<T>&v2)
{
  massert(v.size()==v2.size());
  std::vector<T> result(v.size());
  for(int i=0;i<v.size();++i)
    result[i]=v[i]*v2[i];
  return result;
}

template<class T>
std::vector<T> operator+(std::vector<T>&v,const std::vector<T>&v2)
{
  massert(v.size()==v2.size());
  std::vector<T> result(v.size());
  for(int i=0;i<v.size();++i)
    result[i]=v[i]+v2[i];
  return result;
}

template<class T>
std::vector<T>&operator+=(std::vector<T>&v,const std::vector<T>&v2)
{
  massert(v.size()==v2.size());
  for(int i=0;i<v.size();++i)
    v[i]+=v2[i];
  return v;
}

template<class T>
std::vector<T> operator/(const std::vector<T>&v,double&v2)
{
  std::vector<T> result(v.size());
  for(int i=0;i<v.size();++i)
    result[i]=static_cast<T>(v[i]/v2);
  return result;
}

template<class T>
std::vector<T> operator-(std::vector<T>&v,const std::vector<T>&v2)
{
  massert(v.size()==v2.size());
  std::vector<T> result(v.size());
  for(int i=0;i<v.size();++i)
    result[i]=v[i]-v2[i];
  return result;
}

template<class T>
std::vector<T>&operator+=(std::vector<T>&v,const double v2)
{
  massert(v.size()!=0);
  for(int i=0;i<v.size();++i)
    v[i]+=static_cast<T>(v2);
  return v;
}

#endif
