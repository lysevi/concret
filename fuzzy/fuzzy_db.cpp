#include "fuzzy_db.hpp"


namespace fuzzy
{
  Function*function3(const coord&_min,const coord&_av,const coord&_max)
  {
    coord_vector coords;
    coords.push_back(_min);
    coords.push_back(_av);
    coords.push_back(_max);
    fuzzy::Function *result=new fuzzy::Function(coords);
    return result;
  }

  MinMax find_min_max(const Concrete::CData&cdata,const ivector&numbers)
  {
    int x_length=cdata.x_count();
    MinMax result={dvector(x_length,0),dvector(x_length,0),-1,-1};

    for(int i=0;i<numbers.size();++i){
    //Максимальные и Минимальные значения X
    for(int j=0;j<x_length;++j){
      if(result.max_x[j]<cdata[numbers[i]]->at(j))
	result.max_x[j]=cdata[numbers[i]]->at(j);
      else
	if(result.min_x[j]>cdata[numbers[i]]->at(j))
	  result.min_x[j]=cdata[numbers[i]]->at(j);
    }
    //Максимальные и Минимальные значения Y
    if(result.max_y<cdata.y_for_xp(numbers[i]))
      result.max_y=cdata.y_for_xp(numbers[i]);
    else
      if(result.min_y>cdata.y_for_xp(numbers[i]))
	result.min_y=cdata.y_for_xp(numbers[i]);
    }
    return result;
  }

  MyuFunctions make_myu_functions(const MinMax&minmax)
  {
    const int x_length=minmax.max_x.size();

    Function*y_function=function3(coord(minmax.min_y,0),
				  coord((minmax.max_y+minmax.min_y)/2.0,1.0),
				  coord(minmax.max_y,0));
    
    MyuFunctions result={fvector(0),y_function};
    
    for(int i=0;i<x_length;++i){
      Function*max_f=function3(coord(minmax.min_x[i],0),coord((minmax.max_x[i]+minmax.min_x[i])/2.0,1.0),
			       coord(minmax.max_x[i],0));
    
      Function*min_f=function3(coord(minmax.min_x[i],1),coord((minmax.max_x[i]+minmax.min_x[i])/2.0,0),
			       coord(minmax.max_x[i],1));
      result.x_funcs.push_back(max_f);
      result.x_funcs.push_back(min_f);
    }
    return result;
  }

  // @todo: функция должна уменьшать количество правил.
  fuzzy::rule_vector make_rules(const Concrete::CData&cdata,const MyuFunctions&mf,const ivector&numbers)
  {
    const int x_length=cdata.x_count();
    fuzzy::rule_vector result;
    for(int i=0;i<numbers.size();++i){
      fuzzy::Rule rule;
      for(int x=0;x<x_length;++x){
	int num=-1;            // номер функции для текущего x с максимальной принадлженостью
	double max_value=-1;   // Маскимальная принадлежность x к правилу num
	for(int f=0;f<mf.x_funcs.size();++f){
	  double cur_value=(*mf.x_funcs[f])(cdata[numbers[i]]->at(x));
	  if(cur_value>max_value){
	    max_value=cur_value;
	    num=f;
	  }
	}
	rule.push_back(mf.x_funcs[num]);
      }
      rule.set_y(cdata.y_for_xp(i));
      result.push_back(rule);
    }
    return result;
  }

  // @todo: Реализовать.
  fuzzy::rule_vector compress_fuzzy_db(const Concrete::CData&cdata,const fuzzy::rule_vector&fv)
  {
    fuzzy::rule_vector result;
    for(int i=0;i<fv.size();++i){
      for(int j=0;j<cdata.size();++j){
	
      }
    }
    return fv;
  }
};// namespace fuzzy
