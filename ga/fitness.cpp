#include "fitness.hpp"
#include <cmath>

fitness::fitness(std::string name):m_name(name)
{}

fitness::fitness(int size,std::string name):m_size(size),
					    m_name(name)
{
}

double fitness::operator()(const p_dna&d)
{return 0.1;}

int fitness::size()
{
  return m_size;
}

double fitness::max_distance(const p_dna&d)
{return 0.0;}
