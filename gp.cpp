#include <ga/ga.hpp>

#include <tree/generator.hpp>
#include <tree/crossover.hpp>
#include <tree/mutator.hpp>
#include <tree/functions.hpp>

#include <boost/lexical_cast.hpp>

const double target_value=8.0; // ГОСТ 10180-09
const double mtn_raiting=0.9;
const int    resize_data=1; // для BOOTSTRAP

int    psize=50;
int    max_steps=100;
int    max_depth=5;
double percent_to_learn=0.5;
double selection_percent=0.4;
bool   print_only_best=false;

int main(int argc,char*argv[])
{
  if(argc<2){
    LOG("usage: "<<argv[0]<<" data.csv");
    return -1;
  }
  if(argc==3)
    print_only_best=true;  
  Concrete::CData cdata(argv[1]);
  cdata.init();

  Concrete::CData bt_cdata=cdata.bootstrap(resize_data,0.05);

  Tree::FunctionDB* fdb=Tree::std_functions_db();

  fdb->add_variables(bt_cdata.x_count());

  //for(double i=-10.0;i<10.0;i+=0.5)
  //  fdb->add_constant(i);

  Tree::Generator*gnrt=new Tree::Generator(fdb,max_depth);
  Tree::Crossover*crossover=new Tree::Crossover;
  Tree::Mutator   mtr(gnrt,crossover);

  GpGenerator *dg=new GpGenerator(gnrt);
  //bin_dna_generator *dg=new GpGeneratorHist(fdb,max_depth);

  selector    *sel_r=new rnd_selector;
  GpMutator   *gp_mtn=new GpMutator(gnrt,crossover,fdb);
  GpCrossover*c=new GpCrossover(fdb,crossover);
  
  //std_ga* sg=new hist_gp(sel_r,gp_mtn,c,dg,10);
  std_ga* sg=new std_ga(sel_r,gp_mtn,c,dg);

  GpFitness*ftn=new GpFitness(percent_to_learn,&bt_cdata,fdb);
  sg->set_params(make_params(mtn_raiting,0.4,psize));
  sg->setFitness(ftn);
  sg->init();
  solution sln=sg->getSolution(max_steps,target_value,true,print_only_best);
  LOG("results: "<<sln.first);
  ftn->check_solution(sln.second,&cdata);
}
