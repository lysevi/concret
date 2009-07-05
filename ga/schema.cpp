#include "schema.hpp"
#include <algorithm>
#include <utils/utils.hpp>

bool schema::operator==(const schema&other)
{
  return (this->symbols==other.symbols);
}

bool is_all_star(const schema&s)
{
  symbol_list::const_iterator pos=s.symbols.begin();
  for(;pos!=s.symbols.end();++pos)
    if(pos->second!=-1)
      return false;
  return true;
}


bool is_not_all_star(const schema&s)
{
  symbol_list::const_iterator pos=s.symbols.begin();
  for(;pos!=s.symbols.end();++pos)
    if(pos->second==-1)
      return false;
  return true;
}

scheme_db merge_sdb(const scheme_db&sdb)
{
  scheme_db result(sdb);
  result.erase(std::remove_if(result.begin(),result.end(), is_all_star),result.end());
  result.erase(std::remove_if(result.begin(),result.end(), is_not_all_star),result.end());
  result.erase(unique(result.begin(),result.end()),
	       result.end());
  return result;
}

symbol_list bestSchema(const scheme_db&sdb)
{
  if(sdb.size()==0){
    return symbol_list();
  }
  symbol_list scheme=sdb.begin()->symbols;
  double best_ftn=sdb.begin()->ftn;
  for(scheme_db::const_iterator pos=sdb.begin(); pos!=sdb.end();++pos){
    if(best_ftn>pos->ftn){
      best_ftn=pos->ftn;
      scheme=pos->symbols;
    }
  }
  return scheme;
}
