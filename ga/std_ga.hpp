#ifndef _std_ga
#define _std_ga

#include <ga/params.hpp>
#include <ga/selector.hpp>
#include <string>
#include <map>
using namespace std;

typedef pair<int,p_dna> solution;

class dna;
class selector;
class mutator;
class crossover;
class fitness;
class bin_dna_generator;

// Какую популяцию сейчас использовать.
enum populationNumber{
  FIRST_POPULATION,
  SECOND_POPULATION
};

class std_ga
{
  typedef std::map<ivector,double> FtnCache;
public:
  std_ga(selector*s,mutator*m,crossover*c,bin_dna_generator*g);
  void set_params(const params&param);
  virtual void addIndivid(const p_dna&individ);
  virtual string name()const          {return m_name;}
  virtual void addSuffix(string name) {m_name+=name;}
  virtual ~std_ga();
  virtual void   init();
  virtual void   clean();
  virtual double oneStep();
  virtual solution  getSolution(int max_steps,double min_ftn,bool verbose=false,bool only_best=false);
  virtual void   setFitness(fitness*ftn);

  virtual family_vector select(const population&p,int count);

  void enable_dump();
  void disable_dump();
protected:
  double      calc_ftn(const p_dna&individ);
  population* cur_population();
  population* other_population();
  void        switch_population();
public:
  FtnCache         m_cache;
  population      *m_p_first;
  population      *m_p_second;
  populationNumber m_p_number;
  unsigned int     m_p_position;
  
  selector  *m_s;
  mutator   *m_m;
  crossover *m_c;
  fitness   *m_f;
  bin_dna_generator*m_g;
  params     m_param;
  string     m_name;
  bool       m_dump_enable;
  int        m_generation_number; // номер поколения
  dvector    m_times;             // содержит среднее время по последним 10 замерам.
  int        m_times_index;       // текущий номер в m_times для записи.
};

#endif
