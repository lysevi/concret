#ifndef _niche_hpp_
#define _niche_hpp_

#include <ga/dna.hpp>
#include <ga/population.hpp>
#include <cluster/cmeans.hpp>

typedef cmeans<dna::gvector> dna_cmeans;
typedef dna_cmeans::u_vector data_vector;

data_vector fill_data_vector(const population&p);

#endif
