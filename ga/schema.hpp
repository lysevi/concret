#ifndef _schema_hpp_
#define _schema_hpp_

#include <list>
#include <string>

typedef std::list<std::pair<int,int> > symbol_list; //символ-позиция

struct schema
{
  symbol_list symbols;
  double ftn; //среднее значение фитнесса для кластера, от куда взяли схемы
  bool operator==(const schema&other);
};

typedef std::list<schema> scheme_db;

scheme_db merge_sdb(const scheme_db&sdb);
symbol_list bestSchema(const scheme_db&sdb); // возвращает схему с лучшим фитнессом
#endif
