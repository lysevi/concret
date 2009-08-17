#include <ga/ga.hpp>

#include <tree/root_generator.hpp>
#include <tree/limit_crossover.hpp>
#include <tree/mutator.hpp>
#include <tree/functions.hpp>

#include <fuzzy/rule.hpp>
#include <fuzzy/fuzzy_db.hpp>

#include <boost/lexical_cast.hpp>

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
const double mtn_raiting=1.0;
const int    resize_data=1; // для BOOTSTRAP

int    psize=200;
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

  // Создаем список случайных индексов для обучения системы
  ivector numbers=Concrete::make_learn_indexes(cdata.size(),percent_to_learn);
  
  fuzzy::MinMax minmax=fuzzy::find_min_max(bt_cdata,numbers);

  // Построение функций принадлжености
  fuzzy::MyuFunctions mf=fuzzy::make_myu_functions(minmax);

  LOG("Количество функций для X: "<<mf.x_funcs.size());

  fuzzy::rule_vector rules=fuzzy::make_rules(bt_cdata,mf,numbers);

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
  // количество_if(количество правил) +
  // количество акцедентов.
  max_depth=1+rules.size()+cdata.x_count();

  Tree::Generator*gnrt=new Tree::RootGenerator(fdb,max_depth,fuzzy_fdb->root_number,fuzzy_fdb->second_layer);
  ivector limits;
  limits<<fuzzy_fdb->root_number<<fuzzy_fdb->second_layer;
  Tree::Crossover*crossover=new Tree::LimitCrossover(limits);
  Tree::Mutator   mtr(gnrt,crossover);

  GpGenerator *dg=new GpGenerator(gnrt);

  selector    *sel_r=new rnd_selector;
  GpMutator   *gp_mtn=new GpMutator(gnrt,crossover,fdb);
  GpCrossover*c=new GpCrossover(fdb,crossover);
  
  std_ga* sg=new std_ga(sel_r,gp_mtn,c,dg);

  GpFitness*ftn=new GpFitness(percent_to_learn,&bt_cdata,fdb);
  ftn->set_numbers(numbers);
  sg->set_params(make_params(mtn_raiting,0.4,psize));
  sg->setFitness(ftn);
  sg->init();
  solution sln=sg->getSolution(max_steps,target_value,true,print_only_best);
  LOG("results: "<<sln.first);
  ftn->check_solution(sln.second,&cdata);
}
