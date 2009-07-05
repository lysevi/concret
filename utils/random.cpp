#include "random.hpp"
#include <cstdlib>
#include <ctime>
#include <utils/utils.hpp>

#include <boost/random.hpp>

using namespace boost;

static  mt19937 rng;
static  bool isInit=false;

Random::Random()
{
  if(!isInit){
    rng.seed(static_cast<unsigned> (std::time(0)));
    isInit=true;
  }
}

int Random::uniform(int from,int to)const
{
  boost::uniform_int<> value(from,to);
   boost::variate_generator<boost::mt19937&, boost::uniform_int<> >
     die(rng, value);
   return die();
}

double Random::uniform(double from,double to)const
{
  boost::uniform_real<> value(from,to);
  boost::variate_generator<boost::mt19937&, boost::uniform_real<> >
    die(rng, value);
   return die();
}
