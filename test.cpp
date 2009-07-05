#include <ga/ga.hpp>

tester test;

void add_ftns()
{
  const double std_stop_value=0.1E-02;

//   test.addTest(make_test(new bin_fitness(),
// 			 make_params(0.9,0.2,30),
// 			 -10,10,
// 			 std_stop_value));

//   test.addTest(make_test(new bin_fitness(20),
// 			 make_params(0.9,0.2,70),
// 			 -20,20,
// 			 0.0001));
  
    
//   test.addTest(make_test(new bin_fitness(50),
// 			 make_params(0.9,0.2,100),
// 			 -100,100,
// 			 0.1,100));

//   test.addTest(make_test(new bin_haupt1(),
// 			 make_params(0.9,0.5,30),
// 			 -10,10,
// 			 std_stop_value));
  
//   test.addTest(make_test(new bin_haupt2(),
// 			 make_params(0.9,0.5,30),
// 			 -10,10,
// 			 std_stop_value));

//   test.addTest(make_test(new bin_haupt3(),
// 			 make_params(0.9,0.5,30),
// 			 -10,10,
// 			 std_stop_value));


//   test.addTest(make_test(new bin_haupt4(),
// 			 make_params(0.9,0.5,30),
// 			 -10,10,
// 			 std_stop_value));


// //   // Все равно не сходится  
// //   test.addTest(make_test(new bin_haupt5(),
// // 			 make_params(0.9,0.5,30),
// // 			 -2,2,
// // 			 std_stop_value,100000));
//   // Также
//   test.addTest(make_test(new bin_haupt6(),
// 			 make_params(1.0,0.2,50),
// 			 -10,10,
// 			 0.1,100000));

//   test.addTest(make_test(new bin_haupt10(),
// 			 make_params(0.9,0.5,30),
// 			 -10,10,
// 			 std_stop_value));

//   test.addTest(make_test(new bin_haupt11(),
// 			 make_params(0.9,0.5,30),
// 			 -10,10,
// 			 std_stop_value));

//   test.addTest(make_test(new bin_summ(2000*3),
// 			 make_params(0.9,1.0,50),
// 			 -10,10,
// 			 std_stop_value));


//   test.addTest(make_test(new bin_rosenbrock(2),
// 			 make_params(0.9,0.4,50),
// 			 -2,2,
// 			 std_stop_value));
//   test.addTest(make_test(new bin_rosenbrock(4),
// 			 make_params(0.9,0.4,100),
// 			 -2,2,
// 			 std_stop_value));
//   test.addTest(make_test(new bin_rosenbrock(10),
// 			 make_params(0.9,0.4,100),
// 			 -2,2,
// 			 std_stop_value));
//   test.addTest(make_test(new bin_rosenbrock(100),
// 			 make_params(0.9,0.4,400),
// 			 -2,2,
// 			 std_stop_value));
}

int main(int argc,char*argv[])
{
  add_ftns();
  const short mtn_bit_count=10;
  bin_crossover*b_crv_canon=new bin_crossover(true);
  bin_crossover*b_crv=new bin_crossover;
  bin_mutator  *b_mtn=new bin_mutator(mtn_bit_count);

  // Генератор должен получать диапазон от test_suite
  bin_dna_generator *b_dg=new bin_dna_generator;

  selector*     sel_r=new rnd_selector;
  niche_selector* sel_n=new niche_selector;

  std_ga* sg=new std_ga(sel_r,b_mtn,b_crv_canon,b_dg);
  std_ga* sg2=new std_ga(sel_r,b_mtn,b_crv,b_dg);
  sg2->addSuffix("+CRV");

  scheme_dna_generator* sgen=new scheme_dna_generator();
  scheme_dna_generator* sgen_not=new scheme_dna_generator(false);

  scheme_mutator*sch_mtn=new scheme_mutator(mtn_bit_count);

  std_ga* niche=new niche_ga(sel_r,b_mtn,b_crv,b_dg);

  std_ga* sch_ga=new scheme_ga(sel_r,b_mtn,b_crv_canon,sgen,false);
  std_ga* sch_ga_not=new scheme_ga(sel_r,sch_mtn,b_crv_canon,sgen_not);
  sch_ga_not->addSuffix("-Mutator");
  std_ga* sch_ga_gm=new scheme_ga(sel_r,sch_mtn,b_crv_canon,sgen);
  sch_ga_gm->addSuffix("-GeneratorAndMutator");

  bin_mutator*mgen_mtn=new mgen_mutator(mtn_bit_count);
  bin_crossover*mgen_crv=new mgen_crossover;
  bin_dna_generator*mgen_gnrt=new mgen_dna_generator;
  std_ga* mgen_sg=new std_ga(sel_r,mgen_mtn,mgen_crv,mgen_gnrt);
  mgen_sg->addSuffix("-MGen");

  //sg->enable_dump();
  test.addGA(sg);
//   test.addGA(niche);
//   test.addGA(sch_ga);
//   test.addGA(sch_ga_not);
//   test.addGA(sch_ga_gm);
//  test.addGA(mgen_sg);
  test.run(1,1);
}
/*
-*- mode: compilation; default-directory: "~/develop/mga/" -*-
Compilation started at Fri Jan 16 18:03:02
make test
[  0%] Built target Tags
[ 12%] Built target utils
[ 92%] Built target ga
[ 96%] Built target ga_test
[ 96%] running ga test
std_ga
diafant_4: 10000 10000 3815 10000 10000 10000 10000 10000 10000 1966
Steps=8578 ftn=0.000402 time= 5.72
diafant_20: 10000 10000 10000 10000 10000 10000 10000 10000 10000 10000
Steps=10000 ftn=0.000859 time= 38.6
haupt1: 10000 10000 1536 10000 10000 10000 4033 10000 10000 10000
Steps=8556 ftn=3.18547e-05 time= 8.77
haupt2: 4 1 14 6 16 2 0 0 6 6
Steps=5 ftn=2.91664e-06 time= 0.01
haupt3: 10000 10000 5794 10000 10000 10000 6514 10000 10000 10000
Steps=9230 ftn=2.9001e-05 time= 9.66
haupt4: 10000 10000 10000 10000 10000 6892 10000 10000 10000 10000
Steps=9689 ftn=0.000147837 time= 10.65
haupt10: 1210 10000 10000 10000 9866 10000 10000 10000 10000 10000
Steps=9107 ftn=7.99052e-05 time= 10.08
haupt11: 269 95 105 327 245 85 453 150 309 297
Steps=233 ftn=5.41488e-06 time= 0.27
niche_ga
diafant_4: 10000 529 10000 10000 4647 10000 1286 10000 10000 10000
Steps=7646 ftn=0.000145 time= 112.32
diafant_20: 10000 10000 10000 10000 10000 10000 10000 10000 10000 10000
Steps=10000 ftn=0.003163 time= -433.877
haupt1: 8060 10000 10000 2209 1603 112 2737 2276 10000 1180
Steps=4817 ftn=7.34817e-06 time= 46.71
haupt2: 0 1 1 3 1 0 11 1 0 0
Steps=1 ftn=3.5542e-06 time= 0.05
haupt3: 10000 10000 10000 10000 8471 10000 119 771 1079 10000
Steps=7044 ftn=2.09847e-05 time= 121.5
haupt4: 10000 2539 5882 6295 10000 1174 10000 10000 10000 10000
Steps=7589 ftn=4.75959e-05 time= 114.17
haupt10: 10000 5281 10000 148 10000 10000 10000 10000 10000 10000
Steps=8542 ftn=0.000142165 time= 139.91
haupt11: 10000 210 2106 10000 3569 4026 4133 3290 9922 3204
Steps=5046 ftn=1.22999e-05 time= 40.06
schema_ga
diafant_4: 2676 3971 2129 10000 2289 5721 774 1175 10000 10000
Steps=4873 ftn=0.000142 time= 5.8
diafant_20: 10000 960 10000 10000 10000 10000 10000 10000 3014 10000
Steps=8397 ftn=0.001322 time= 142.91
haupt1: 3968 10000 5267 10000 4428 579 10000 10000 10000 2088
Steps=6633 ftn=2.154e-05 time= 9.21
haupt2: 16 2 9 1 30 0 11 33 3 15
Steps=12 ftn=2.27635e-06 time= 0.02
haupt3: 10000 10000 10000 10000 5613 10000 10000 1903 10000 10000
Steps=8751 ftn=2.70778e-05 time= 13.14
haupt4: 10000 10000 3425 4661 4300 10000 10000 10000 10000 10000
Steps=8238 ftn=8.64339e-05 time= 12.55
haupt10: 10000 10000 10000 10000 10000 10000 10000 7979 10000 2882
Steps=9086 ftn=0.000109326 time= 13.85
haupt11: 264 12 147 626 75 5 238 17 49 208
Steps=164 ftn=3.41505e-06 time= 0.26
[100%] Built target test

Compilation finished at Fri Jan 16 19:24:42
*/
/*
-*- mode: compilation; default-directory: "~/develop/mga/" -*-
Compilation started at Sun Jan 18 12:54:48

make test
[  0%] Built target Tags
[ 11%] Built target utils
[ 92%] Built target ga
[ 96%] Built target ga_test
[ 96%] running ga test
schema_ga-Mutator
diafant_4: 2621 2281 10000 9385 2799 10000 1652 10000 10000 10000
Steps=6873.8 ftn=0.000136 time= 8.48
diafant_20: 10000 10000 10000 10000 10000 4564 3725 10000 10000 10000
Steps=8828.9 ftn=0.000629 time= 164.81
diafant_50: 233 2453 37 774 75 874 865 459 343 2312
Steps=842.5 ftn=0.058296 time= 53.66
haupt1: 10000 10000 5092 10000 913 10000 3715 10000 10000 4335
Steps=7405.5 ftn=2.74329e-05 time= 10.43
haupt2: 24 24 0 2 13 6 10 17 6 0
Steps=10.2 ftn=2.00305e-06 time= 0.01
haupt3: 10000 5865 10000 10000 946 10000 10000 8522 10000 3188
Steps=7852.1 ftn=1.80008e-05 time= 11.83
haupt4: 10000 10000 3340 10000 10000 10000 10000 10000 10000 10000
Steps=9334 ftn=0.000100033 time= 14.44
haupt10: 10000 10000 9253 4130 2930 1834 10000 10000 10000 10000
Steps=7814.7 ftn=8.80714e-05 time= 12.1
haupt11: 392 642 304 223 293 472 584 695 174 555
Steps=433.4 ftn=3.56961e-06 time= 0.69
[100%] Built target test

Compilation finished at Sun Jan 18 12:58:11

*/

/*-*- mode: compilation; default-directory: "~/develop/mga/" -*-
Compilation started at Sun Jan 18 13:05:43

make test
[  0%] Built target Tags
[ 11%] Built target utils
[ 92%] Built target ga
[ 96%] Built target ga_test
[ 96%] running ga test
schema_ga-GeneratorAndMutator
diafant_4: 6227 7415 10000 10000 822 10000 10000 10000 278 49
Steps=6479.1 ftn=0.000145 time= 7.81
diafant_20: 10000 10000 10000 10000 10000 10000 10000 10000 10000 10000
Steps=10000 ftn=0.000507 time= 129.41
diafant_50: 134 2432 1025 25 57 291 202 42 6 40
Steps=425.4 ftn=0.0432 time= 23.78
haupt2: 0 1 12 10 5 6 9 18 1 8
Steps=7 ftn=4.19086e-06 time= 0.01
haupt3: 10000 9704 10000 6799 10000 10000 10000 10000 3824 2579
Steps=8290.6 ftn=2.0064e-05 time= 13.65
haupt4: 10000 10000 10000 5890 10000 8629 10000 10000 10000 10000
Steps=9451.9 ftn=6.98061e-05 time= 15.6
haupt10: 10000 2334 10000 10000 6422 2307 10000 10000 10000 10000
Steps=8106.3 ftn=4.79684e-05 time= 13.43
haupt11: 56 16 11 4 35 39 2 8 149 203
Steps=52.3 ftn=3.1136e-06 time= 0.09
*/
