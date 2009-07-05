#ifndef _cmeans_
#define _cmeans_

#include <utils/utils.hpp>
#include <utils/math_funcs.hpp>
#include <utils/random.hpp>
#include <utils/vector_op.hpp>
#include <vector>
#include <functional>
#include <cmath>
#include <map>
const double g_about_null = 1e-8;

typedef std::pair<int,double>        cluster_element;        //номер-мера принадлежности к кластеру.
typedef std::vector<cluster_element> cluster_vector;
typedef std::map<int,cluster_vector>  clusters;

/// U - data type
template <class U>
class cmeans
{
public:
  typedef std::vector<double> t_vector;
  typedef std::vector<t_vector> part_matrix;
  typedef std::vector<U> u_vector;
  typedef std::vector<u_vector> u_matrix;
  u_vector m_center_sequence;
  struct result
  {
    part_matrix u;
    u_vector    c;
    double      error;
    int         steps;
  };
  cmeans(){};
  part_matrix init_partion_matrix(int clusters_num,int points_num)
  {
    Random rh;
    part_matrix u(clusters_num);
    
    for(int i=0;i<u.size();++i)
      u[i]=std::vector<double>(points_num);
    
    for(int j=points_num-1;j>=0;--j){
      std::vector<double> nv(clusters_num);
      for(int k=0;k<clusters_num;++k)
	nv[k]=rh.uniform(0.0,1.0);
      normalise_seq(nv.begin(),nv.end());
      for(int i=clusters_num-1;i>=0;--i)
	u[i][j]=nv[i];
    }
    return u;
  }
  
  u_vector generate_clusters_center_sequence(const part_matrix&partion_matrix,		 
					     const typename u_vector::const_iterator&data_begin,
					     const typename u_vector::const_iterator&data_end,
					     const int data_size)
  {
    int clusters_num=partion_matrix.size();
    u_vector c(clusters_num);
    typename u_vector::reverse_iterator c_pos=c.rbegin();
    for(int i=clusters_num-1;i>=0;--i){

      U acc(data_begin->size());
      typename u_vector::const_iterator pos=data_begin;
      for(int j=0;j<partion_matrix[i].size();++j){
	U t((*pos*(partion_matrix[i][j]*partion_matrix[i][j])));
	acc+=t;
	++pos;
      }

      double reduce_result;

      for(int k=0;k<partion_matrix[i].size();++k)
	reduce_result+=partion_matrix[i][k]*partion_matrix[i][k];

      *c_pos=acc/reduce_result;
      ++c_pos;
    }
    return c;
  }
  template<class D>
  part_matrix generate_partion_matrix(D distance,
				      const u_vector&clusters_center_sequence,
				      const typename u_vector::const_iterator&data_begin,
				      const typename u_vector::const_iterator&data_end,
				      const int data_size)
  {
    int clusters_num = clusters_center_sequence.size();
    int points_num = data_size;
    part_matrix u(clusters_num);
    for(int i=0;i<clusters_num;++i)
      u[i]=std::vector<double>(points_num);
    
    typename u_vector::const_iterator cluster_pos_i=clusters_center_sequence.begin();
    for(int i=0; i<clusters_num; ++i,++cluster_pos_i) {
      for(int j=0; j<points_num; ++j) {
	double acc = static_cast<double>(g_about_null);
	typename u_vector::const_iterator pos=data_begin;
	typename u_vector::const_iterator cluster_pos=clusters_center_sequence.begin();
	for(int k=0;k<clusters_center_sequence.size();++k){
	  double t = distance(*pos,*cluster_pos);
	  acc += (distance(*pos, *cluster_pos_i) / ((t!=0.0)?t:g_about_null));
	  u[i][j] = 1 / acc;
	  ++pos;
	  ++cluster_pos;
	}
      }
    }
    return u;
  }

  double calculate_error(const part_matrix&current_partion_matrix,const part_matrix&previous_partion_matrix)
  {
    double acc = 0.0;
    int cur_s=current_partion_matrix.size();
    int pr_s=previous_partion_matrix.size();
    for(int i=((cur_s<pr_s)?cur_s:pr_s)-1; i>=0; --i) {
      int cs=current_partion_matrix[i].size();
      int ps=previous_partion_matrix[i].size();
      for(int j=((cs<ps)?cs:ps)-1; j>=0; --j) {
	acc += sqrt(pow(current_partion_matrix[i][j]-previous_partion_matrix[i][j],2.0));
      }
    }
    return acc;
  }
  template<class D>
  result cluster(D distance,
		 int clusters_num,
		 const typename u_vector::const_iterator&data_begin,
		 const typename u_vector::const_iterator&data_end,
		 const int data_size,
		 double accuracy=1.0, 
		 int max_steps=100)
  {
    int points_num = data_size;
    part_matrix u = init_partion_matrix(clusters_num, points_num);
    double error = accuracy;
    part_matrix u_new;
    int step=0;
    for(step = 0; step<max_steps && error >= accuracy; ++step) 
      {
	m_center_sequence = generate_clusters_center_sequence(u, data_begin,data_end,data_size);
	u_new = generate_partion_matrix(distance, m_center_sequence,data_begin,data_end,data_size);
	error = calculate_error(u_new, u);
	u = u_new;
      }
    result res={u_new, m_center_sequence, error, step};
    return res;
  }
  template<class D>
  result cluster(D distance,const typename u_vector::const_iterator&data_begin,
		 const typename u_vector::const_iterator&data_end,
		 const int data_size)
  {
    part_matrix u_new = generate_partion_matrix(distance, m_center_sequence, data_begin,data_end,data_size);
    result res={u_new,m_center_sequence,0,0};
    return res;
  }
  static clusters u2clsuters(const part_matrix&u)
  {
    clusters result;
    for(int d_num=0;d_num<u[0].size();++d_num){
      int    c=0;
      double e=u[c][d_num];
      for(int c_num=0;c_num<u.size();++c_num){
	if(u[c_num][d_num]>e){
	  c=c_num;
	  e=u[c_num][d_num];
	}
      }
      result[c].push_back(std::make_pair(d_num,e));
    }
    return result;
  }
};


#endif
