#include "mutator.hpp"
#include <utils/random.hpp>

mutator::mutator()
{
  m_r=new Random();
}

mutator::~mutator()
{}

double mutator::percent()
{
  return m_r->uniform(0.0,100.0);
}

p_dna mutator::operator()(const p_dna&d,double percent)
{return p_dna(new dna(*d.get()));}
