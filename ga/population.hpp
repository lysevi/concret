#ifndef _population_
#define _population_

#include <utils/utils.hpp>
#include <vector>
#include <ga/dna.hpp>


typedef std::vector<p_dna> population;

p_dna  best(const population&p);
p_dna  worst(const population&p);
p_dna  byIndex(const population&p,int index);
int    indexOfBest(const population&p);

#endif
