#include <utils/utils.hpp>
#include <utils/io.hpp>
#include <cluster/cmeans.hpp>
#include <boost/shared_ptr.hpp>

double distance2(ivector a,ivector b)
{
  double res=0.0;
  ivector z=a-b;
  for(int i=0;i<a.size();++i)
    res+=sqrt(z[i]*z[i]);
  return res;
}

int main()
{
  LOG("++++++++++++++++++++");
  typedef ivector data;
  typedef cmeans<data> data2_cm;
  
  data d1(3);
  d1[0]=1;d1[1]=2;d1[2]=3;
  data d2(3);
  d2[0]=101;d2[1]=22;d2[2]=22;
  data d3(3);
  d3[0]=1;d3[1]=12;d3[2]=23;

  data2_cm cm2;
  data2_cm::u_vector u2_v;
  u2_v.push_back(d1);  u2_v.push_back(d2);  u2_v.push_back(d3);

  data2_cm::result r2=cm2.cluster(distance2,2,u2_v.begin(),u2_v.end(),u2_v.size(),0.001);

  LOG(r2.u);
  LOG(r2.c);
  LOG(r2.error);
  LOG(r2.steps);
  clusters c=data2_cm::u2clsuters(r2.u);
  LOG(c);
}
