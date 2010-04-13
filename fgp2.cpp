#include <ga/ga.hpp>

#include <tree/root_generator.hpp>
#include <tree/limit_crossover.hpp>
#include <tree/mutator.hpp>
#include <tree/functions.hpp>

#include <fuzzy/rule.hpp>
#include <fuzzy/fuzzy_db.hpp>

#include <boost/lexical_cast.hpp>

// Двухуровневый алгоритм настройки базы правил.

class NewFuzzyFunction
{
public:
  NewFuzzyFunction(fuzzy::Function*ff):m_ff(ff){};
  NewFuzzyFunction(const NewFuzzyFunction&other):m_ff(other.m_ff){};
  NewFuzzyFunction&operator=(const NewFuzzyFunction&other){m_ff=other.m_ff;};
  Tree::TermType operator()(Tree::Args args)  {return (*m_ff)(args[0]);};
protected:
  fuzzy::Function *m_ff;
};

const double target_value=8.0; // ГОСТ 10180-09
const double mtn_raiting=0.9;
const int    resize_data=1; // для BOOTSTRAP
const short  mtn_bit_count=10; // количество мутирующих битов в гене

int    psize=200;
int    max_steps=100;
int    max_steps_ga=10;
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
  // Создаем список случайных индексов для обучения системы
  ivector numbers=Concrete::make_learn_indexes(cdata.size(),percent_to_learn);

  
  // Этап 1 - натройка с помощью ГА
  LOG("Этап 1");
  fitness           *sugeno_ftn=new bin_sugeno(&bt_cdata,numbers);
  bin_crossover     *b_crv=new bin_crossover(true);
  bin_mutator       *b_mtn=new bin_mutator(mtn_bit_count);
  bin_dna_generator *b_dg=new bin_dna_generator(0.0,1.0,sugeno_ftn->size());

  LOG("Длина ДНК: "<<sugeno_ftn->size());

  selector*     sel_r=new rnd_selector;
  std_ga* sg=new std_ga(sel_r,b_mtn,b_crv,b_dg);
  sg->set_params(make_params(0.99,0.5,30));
  sg->setFitness(sugeno_ftn);
  sg->init();
  solution sln=sg->getSolution(max_steps_ga,10.0,true);
  // Этап 2 - натройка с помощью ГП
  LOG("Этап 2");
  fuzzy::MinMax minmax=fuzzy::find_min_max(bt_cdata,numbers);

  fuzzy::MyuFunctions mf_old=fuzzy::make_myu_functions(bt_cdata,numbers,minmax);
  fuzzy::MyuFunctions mf={fuzzy::fvector(0),mf_old.y_function};

  // Построение функций принадлжености  
  const int x_count=bt_cdata.x_count();
  int i=0;
  
  for(int k=0;k<bt_cdata.size();++k)
    for(int x=0;x<x_count;++x){
      fuzzy::ExpFunction*ff=new fuzzy::ExpFunction(sln.second->get(i),sln.second->get(i+1));
      mf.x_funcs.push_back(ff);
      i+=2;
    }
  fuzzy::rule_vector rules=fuzzy::make_rules(bt_cdata,mf,numbers);

  LOG("Количество функций для X: "<<mf.x_funcs.size());

  // Настраиваем базу функций ГП

  dvector y(rules.size());
  for(int i=0;i<rules.size();++i){
    y[i]=rules[i].y();
  }
  Tree::FuzzyFDB *fuzzy_fdb=Tree::fuzzy_function_db(y,cdata.x_count());
  Tree::FunctionDB* fdb=fuzzy_fdb->fdb;

  for(int i=0;i<rules.size();++i){
    int j=0;
    for(fuzzy::fvector::const_iterator pos=rules[i].begin();
	pos!=rules[i].end();++pos,j++){
      std::string func_name="f_"+boost::lexical_cast<std::string>(i);
      std::string var_name="x-"+boost::lexical_cast<std::string>(j);
      NewFuzzyFunction ff(*pos);
      fdb->add_function(new Tree::VarFuncNode(func_name,var_name,1,ff));
    }
  }
  
  // sugeno_out+
  //   количество_if(количество правил) +
  //   количество акцедентов.
  max_depth=1+rules.size()+cdata.x_count();

  Tree::Generator*gnrt=new Tree::RootGenerator(fdb,max_depth,fuzzy_fdb->root_number,fuzzy_fdb->second_layer);
  ivector limits;
  limits<<fuzzy_fdb->root_number<<fuzzy_fdb->second_layer;
  Tree::Crossover*crossover=new Tree::LimitCrossover(limits);
  Tree::Mutator   mtr(gnrt,crossover);

  GpGenerator *dg=new GpGenerator(gnrt);

  GpMutator   *gp_mtn=new GpMutator(gnrt,crossover,fdb);
  GpCrossover*c=new GpCrossover(fdb,crossover);
  
  std_ga* gp_sg=new std_ga(sel_r,gp_mtn,c,dg);

  GpFitness*gp_ftn=new GpFitness(percent_to_learn,&bt_cdata,fdb);
  gp_ftn->set_numbers(numbers);
  gp_sg->set_params(make_params(mtn_raiting,0.4,psize));
  gp_sg->setFitness(gp_ftn);
  gp_sg->init();
  solution gp_sln=sg->getSolution(max_steps,target_value,true,print_only_best);
  LOG("results: "<<gp_sln.first);
  gp_ftn->check_solution(gp_sln.second,&cdata);
}
