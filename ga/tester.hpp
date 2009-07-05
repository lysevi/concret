#ifndef _tester_
#define _tester_

#include <ga/fitness.hpp>
#include <ga/params.hpp>
#include <ga/std_ga.hpp>

struct test_suite
{
  fitness*ftn;
  params  pr;
  int     from;
  int     to;
  double  min_ftn;
  int     step_count;
};

test_suite make_test(fitness*ftn,params pr,int from, int to,double min_ftn,int step_count=10000);

typedef std::list<test_suite> test_list;
typedef std::list<std_ga*>    ga_list;

class tester
{
public:
  tester();
  void addTest(test_suite ts);
  void addGA(std_ga*ga);
  void run(int sc,bool verbose=false);
protected:
  test_list m_testes;
  ga_list   m_ga;
};

#endif
