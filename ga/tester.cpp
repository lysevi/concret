#include "population.hpp"
#include <ga/tester.hpp>
#include <ga/bin_dna_generator.hpp>
#include <utils/utils.hpp>
#include <utils/math_funcs.hpp>
#include <boost/timer.hpp>

test_suite make_test(fitness*ftn,params pr,int from, int to,double min_ftn,int step_count)
{
  test_suite res={ftn,pr,from,to,min_ftn,step_count};
  return res;
}

tester::tester()
{}

void tester::addTest(test_suite ts)
{
  m_testes.push_back(ts);
}

void tester::addGA(std_ga*ga)
{
  m_ga.push_back(ga);
}

void tester::run(int sc,bool verbose)
{
  ga_list::iterator ga_pos=m_ga.begin();
  for(;ga_pos!=m_ga.end();++ga_pos){
    std_ga*cur_ga=*ga_pos;
    LOG(cur_ga->name());
    test_list::iterator test_pos=m_testes.begin();
    for(;test_pos!=m_testes.end();++test_pos){
      test_suite ts=*test_pos;
      LOGN(""<<ts.ftn->name()<<":");

      cur_ga->m_g->setFrom(ts.from);
      cur_ga->m_g->setTo(ts.to);

      cur_ga->set_params(ts.pr);
      cur_ga->setFitness(ts.ftn);

      ivector steps(sc);
      dvector ftns(sc);
      boost::timer t0;      //Время выполнения в секундах.

      for(int i=0;i<sc;++i){
	cur_ga->init();

	solution sln=cur_ga->getSolution(ts.step_count,ts.min_ftn,verbose);

	int step_count=sln.first;
	LOGN(' '<<step_count);
	steps[i]=step_count;
	ftns[i]=sln.second->ftn();

	cur_ga->clean();
      }
      LOG("\nSteps="<<static_cast<double>(summ(steps.begin(),steps.end()))/static_cast<double>(steps.size())
	  <<" ftn="<<summ(ftns.begin(),ftns.end())/ftns.size()
	  <<" time= "<<t0.elapsed());
    }
  }
}
