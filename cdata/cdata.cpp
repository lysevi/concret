#include "cdata.hpp"
#include <string>
#include <vector>

#include <fstream>
#include <stdexcept>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <utils/random.hpp>
#include <utils/utils.hpp>
#include <utils/io.hpp>

namespace Concrete
{

  const int kMaxLineLength=1024*10; // Максимальная длина строки в файле

  CData::CData()
  {}
  
  CData::CData(const std::string&xdata_file):m_xdata_file(xdata_file)
  {}

  CData::CData(const CData&other):m_xdata_file(other.m_xdata_file),
				  m_x_matrix(other.m_x_matrix),
				  m_y_vector(other.m_y_vector)
  {}

  CData&CData::operator=(const CData&other)
  {
    if(this==&other)
      return *this;
    m_x_matrix=other.m_x_matrix;
    m_y_vector=other.m_y_vector;
    m_xdata_file=other.m_xdata_file;
    return *this;
  }
  
  void CData::init()
  {
    std::ifstream inputFile_x(m_xdata_file.c_str());
    m_y_vector=p_component(new dvector());

    if(!inputFile_x)
      throw std::logic_error("can`t open file: "+m_xdata_file);

    while(!inputFile_x.eof()){
      char str[kMaxLineLength];
      inputFile_x.getline(str,1024*10);
      std::string s(str);
      
      p_component dv=convert_to_dvector(s);
      if(dv->size()==0)
	continue;

      p_component new_dv(new dvector(dv->size()-1));

      for(int i=0;i<dv->size()-1;++i)
	(*new_dv)[i]=(*dv)[i];

      m_x_matrix.push_back(new_dv);

      m_y_vector->push_back((*dv)[dv->size()-1]);
    }
  
    inputFile_x.close();
  
    LOG("Количество экспериментов: "<<m_y_vector->size());
  }

  p_component CData::convert_to_dvector(const std::string&s)const
  {
    typedef std::vector< std::string > split_vector_type;
    split_vector_type words;
    boost::split(words,s, boost::is_any_of(";"));

    p_component dv(new dvector);

    for(int i=0;i<words.size();++i){
      try{
	boost::trim(words[i]);
	if(words[i].size()==0)
	  continue;
	dv->push_back(boost::lexical_cast<double>(words[i]));
      }
      catch(...){
	LOG("Error when cast: |"<<words[i]<<'|');
      }
    }
    return dv;
  }

  p_component CData::operator[](const int index)const
  {
    return m_x_matrix.at(index);
  }

  double CData::y_for_xp(int index)const
  {
    return m_y_vector->at(index);
  }

  
  int CData::size()const
  {
    return m_y_vector->size();
  }
  
  CData CData::bootstrap(int percent,double delta_size)
  {
    int new_data_length=m_x_matrix.size()*percent;
    CData result;
    Random rnd;
    dmatrix     x_matrix(m_x_matrix.size()*percent);
    p_component y_vector(new dvector(m_y_vector->size()*percent));

    int pos=0;
    for(int i=0;i<m_x_matrix.size();++i){
      for(int j=0;j<percent;++j,++pos){
	p_component new_c=p_component(new dvector(*m_x_matrix.at(i)));
	x_matrix[pos]=new_c;
	
	
	double value=m_y_vector->at(i);
	double delta=value*delta_size;
	y_vector->at(pos)=value+rnd.uniform(-delta,delta);
      }
    }
    result.m_x_matrix=x_matrix;
    result.m_y_vector=y_vector;
    LOG("Увеличенное количество экспериментов: "<<result.m_y_vector->size());    
    return result;
  }

  int CData::x_count()const // количество входных параметров  
  {
    return m_x_matrix[0]->size();
  }

  ivector make_learn_indexes(int data_size,double percent)
  {
    Random rnd;
    ivector result;
    int data_count=data_size;
    int x_count=static_cast<int>(data_count*percent);

    result.resize(x_count);

    for(int i=0;i<x_count;++i){
      if(percent==1)
	result[i]=i;
      else{
	int rnd_index=-1;
	// индексы должны быть уникальными
	do{
	  rnd_index=rnd.uniform(0,data_size-1);
	}while(in(result.begin(),result.end(),rnd_index));
    
	result[i]=rnd_index;
      }
    }
  
    std::sort(result.begin(),result.end());
    return result;
  }
};//namespace Concrete
