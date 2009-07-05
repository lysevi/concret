#include <ga/ga.hpp>

#include <utils/binary.hpp>

#include <tree/tree.hpp>
#include <tree/generator.hpp>
#include <tree/crossover.hpp>
#include <tree/mutator.hpp>
#include <tree/functions.hpp>
#include <tree/node.hpp>

#include <boost/assign/list_inserter.hpp>

#include <cmath>
#include <fstream>
#include <utility>

#include <utils/io.hpp>

const double target_value=0.0;
const int    psize=200;
const double mtn_raiting=0.9;
const int    max_steps=500;

typedef std::pair<double,double> range;
typedef std::list<range> range_list;

class mixture_ftn:public fitness
{
public:
  mixture_ftn(Tree::Tree*t):fitness(0,"mixture_fitness"),
			    m_tree(t)
  {}
  
  double operator()(const p_dna&d)
  {
    Tree::VarMap vm;
    vm["x1"]=bin2real((*d)[0]);
    vm["x2"]=bin2real((*d)[1]);
    vm["x3"]=bin2real((*d)[2]);
    vm["x4"]=bin2real((*d)[3]);
    return fabs(500-m_tree->eval(vm));
  }
protected:
  Tree::Tree*m_tree;
};

class mixture_dna_generator:public bin_dna_generator
{
public:
  mixture_dna_generator(const range_list&rl):m_ranges(rl)
  {}

  p_dna generate()
  {
    const int dna_size=m_ranges.size();
    p_dna result(new dna(dna_size));

    range_list::const_iterator pos=m_ranges.begin();

    for(int i=0;pos!=m_ranges.end();++pos,++i)
      (*result)[i]=real2bin(m_rnd.uniform(pos->first,pos->second));
    return result;
  }
protected:
  range_list m_ranges;
};

int main(int argc,char*argv[])
{
  if(argc!=2){
    LOG("usage: "<<argv[0]<<" path_to_tree_file.out");
    return -1;
  }
 
  Tree::FunctionDB* fdb=Tree::std_functions_db();

  fdb->add_variable("x1");
  fdb->add_variable("x2");
  fdb->add_variable("x3");
  fdb->add_variable("x4");
  //fdb->add_variable("x5");

  range_list rl;

  boost::assign::push_back(rl)(30,70)
    (10,30)
    (9,26)
    (8,15);

  Tree::Tree*t=new Tree::Tree;
  t->set_fdb(fdb);

  {
    std::ifstream ifile(argv[1]);
    char line[1024*5];
    ifile.getline(line,1024*5-1);
    t->restore_from_str(line);
    LOG("loaded tree: "<<t->to_str());
  }
  


  const short mtn_bit_count=10;
  
  bin_crossover*b_crv=new bin_crossover;
  bin_mutator  *b_mtn=new bin_mutator(mtn_bit_count);

  // Генератор должен получать диапазон от test_suite
  mixture_dna_generator *b_dg=new mixture_dna_generator(rl);
  selector*     sel_r=new rnd_selector;

  fitness*ftn=new mixture_ftn(t);

  std_ga* sg=new std_ga(sel_r,b_mtn,b_crv,b_dg);

  sg->set_params(make_params(mtn_raiting,0.4,psize));
  sg->setFitness(ftn);
  sg->init();
  
  solution sln=sg->getSolution(max_steps,target_value,true);
}
