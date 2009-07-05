#include <stdexcept>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include <vector>
#include <utils/random.hpp>
#include <tree/tree.hpp>
#include <tree/node.hpp>
#include <tree/function_db.hpp>
#include <tree/generator.hpp>
#include <tree/root_generator.hpp>
#include <tree/crossover.hpp>
#include <tree/limit_crossover.hpp>
#include <tree/mutator.hpp>

#include <utils/utils.hpp>
#include <utils/io.hpp>

Tree::TermType add(Tree::Args args)
{
  return args[0]+args[1];
}

Tree::TermType sub(Tree::Args args)
{
  return args[0]-args[1];
}

Tree::TermType mul(Tree::Args args)
{
  return args[0]*args[1];
}

Tree::TermType inc(Tree::Args args)
{
  return args[0]+1;
}

Tree::TermType div_func(Tree::Args args)
{
  if (args[1]!=0)
    return args[0]/args[1];
  else
    return args[0];
}

int main(int argc,char*argv[])
{
  Tree::FunctionDB* fdb=new Tree::FunctionDB;
  fdb->add_function(new Tree::FunctionNode("+",2,add)); // 0
  fdb->add_function(new Tree::FunctionNode("-",2,sub)); // 1
  fdb->add_function(new Tree::FunctionNode("*",2,mul)); // 2
  fdb->add_function(new Tree::FunctionNode("/",2,div_func)); //3
  
  fdb->add_variable("x1"); // 4
  fdb->add_variable("x2"); // 5

  for(double i=0.0;i<1.0;i+=0.1)
    fdb->add_constant(i);

  LOG("functions="<<fdb->functions());
  LOG("variables="<<fdb->variables());
  LOG("constants="<<fdb->constants());

  Tree::Tree t3;
  t3.set_fdb(fdb);
  int root=t3.add_node(0); // +
  int x1=t3.add_node(4);   // x1
  int x2=t3.add_node(5);   // x5

  t3.connect(root,x1);
  t3.connect(root,x2);

  t3.set_root(root);
  LOG(t3.to_str());
  Tree::VarMap vm;
  vm["x1"]=1;
  vm["x2"]=2;

  LOG("Eval test")
  if(t3.eval(vm)!=3){
    throw std::logic_error("test_error : t3.eval(vm)!=3,"+boost::lexical_cast<std::string>(t3.eval(vm)));
  }
  
  LOG("Flat test")
  ivector flat_test;
  flat_test<<0<<0<<1<<0<<2<<-1<<0<<0<<1<<4<<2<<5;
  if(t3.flat()!=flat_test){
    LOG(t3.flat());
    throw std::logic_error("test_error : t3.flat()");
  }

  Tree::Tree t4(fdb,t3.flat());
  LOG(t4.to_str());
  LOG("Sub tree");
  LOG(t4.sub_tree(t4.root()).to_str());
  t4.remove_node(t4.root());

  if(t4.size()!=0){
    LOG(t4.size());
    throw std::logic_error("test_error : t4.size()");
  }
  LOG("SetSubTree");
  Tree::Tree t33=t3.clone();
  t3.set_sub_tree(x1,t33);
  LOG("t3 "<<t3.to_str());
  LOG("sub_tree "<<t3.sub_tree(t3.root()).to_str());

  Tree::Tree t_sc2;
  t_sc2.set_fdb(fdb);
  int sc_02=t_sc2.add_node(8);   // 0.2
  t_sc2.set_root(sc_02);
  LOG("sub_tree: "<<t_sc2.sub_tree(t_sc2.root()).to_str())

  LOG("Generator test");
  Tree::Generator*gnrt=new Tree::Generator(fdb,2);

  for(int i=0;i<5;++i){
    Tree::Tree t(gnrt->generate());
    LOG(" ==> "<<t.eval(vm));
  }

  LOG("Root Generator");
  Tree::Generator*root_gnrt=new Tree::RootGenerator(fdb,2,0,1);
  for(int i=0;i<5;++i){
    Tree::Tree t(root_gnrt->generate());
    LOG(" ==> "<<t.to_str());
    LOG(" ++> "<<t.eval(vm));
  }


  LOG("Crossover test");
  Tree::Crossover crossover;
  for(int i=0;i<10;++i){
    Tree::Tree f(gnrt->generate());
    Tree::Tree m(gnrt->generate());
    LOG(' '<<f.eval(vm));
    LOG(' '<<f.eval(vm));
    Tree::Tree child=crossover.cross(f,m);
    LOG("child="<<child.eval(vm));
  }

  LOG("Limit test");
  ivector limits;
  limits<<0<<1;
  Tree::Crossover*limit_crossover=new Tree::LimitCrossover(limits);
  for(int i=0;i<10;++i){
    Tree::Tree f(gnrt->generate());
    Tree::Tree m(gnrt->generate());
    LOG(' '<<f.to_str());
    LOG(' '<<f.to_str());
    Tree::Tree child=limit_crossover->cross(f,m);
    LOG("child="<<child.to_str());
  }

  LOG("Mutator test");
  Tree::Tree f(gnrt->generate());
  Tree::Mutator mtr(gnrt,&crossover);
  Tree::Tree mutant=mtr.mutate(f,1.0);
  LOG("mutatnt="<<mutant.to_str()<<" => "<<mutant.eval(vm));

  std::string mtn_string=mutant.save_to_str();
  f.restore_from_str(mtn_string);
  LOG("loaded="<<f.to_str());

  LOG("compress tree");

  Tree::Tree t_c;
  t_c.set_fdb(fdb);
  root=t_c.add_node(0);        // +
  int left=t_c.add_node(6);    // 0.0
  int right=t_c.add_node(7);   // 0.1
  t_c.set_root(root);
  t_c.connect(root,left);
  t_c.connect(root,right);
  LOG("+t_c="<<t_c.to_str()<<" "<<t_c.flat());
  t_c.compress_const_expr();
  LOG("-t_c="<<t_c.to_str()<<" "<<t_c.flat());
  t_c.compress_const_expr();
  LOG("=t_c="<<t_c.to_str()<<" "<<t_c.flat());
  
  LOG("compress tree 2");

  Tree::Tree t_c2;
  t_c2.set_fdb(fdb);
  int plus=t_c2.add_node(0);   // +
  int minus=t_c2.add_node(1);  // -
  int c_01=t_c2.add_node(7);   // 0.1
  int c_02=t_c2.add_node(8);   // 0.2
  int v=t_c2.add_node(4);      // x1

  t_c2.set_root(plus);
  t_c2.connect(plus,minus);
  t_c2.connect(plus,v);
  t_c2.connect(minus,c_01);
  t_c2.connect(minus,c_02);

  LOG("+t_c2="<<t_c2.to_str()<<" "<<t_c2.flat());
  t_c2.compress_const_expr();
  LOG("-t_c2="<<t_c2.to_str()<<" "<<t_c2.flat());
  LOG("FUZZY")
  {
      Tree::FunctionDB* ffdb=new Tree::FunctionDB;
      ffdb->add_function(new Tree::FunctionNode("+",2,add)); // 0
      ffdb->add_function(new Tree::FunctionNode("-",2,sub)); // 1
      ffdb->add_function(new Tree::FunctionNode("*",2,mul)); // 2
      int number_of_inc=ffdb->add_function(new Tree::VarFuncNode("++","x1",1,inc)); //4

      ffdb->add_variable("x1"); // 4


      Tree::Tree ft;
      ft.set_fdb(ffdb);
      int froot=ft.add_node(number_of_inc); // ++
      ft.set_root(froot);
      
      Tree::VarMap fvm;
      fvm["x1"]=1;
      LOG(" >>> 2=="<<ft.eval(fvm)<<" : "<<ft.to_str());

      LOG("Generator test");
      Tree::Generator*gnrt=new Tree::Generator(ffdb,2);

      for(int i=0;i<5;++i){
	Tree::Tree t(gnrt->generate());
	LOG(" ==> "<<t.to_str()<<" -> "<<t.eval(fvm));
      }
  }
}
