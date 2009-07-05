#ifndef _value_hpp_
#define _value_hpp_

#include <string>
#include <vector>

namespace fuzzy
{
  class Value
  {
  public:
    Value();
    explicit Value(double myu);
    Value(const Value&other);
    Value operator=(const Value&other);
    Value operator+=(const Value&other);
    double myu()const;
    Value operator&&(const Value&other)const;
    Value operator||(const Value&other)const;
    Value operator!()const;
    Value operator+(const Value&other)const;
    Value operator-(const Value&other)const;
    Value operator/(const Value&other)const;
    Value operator*(const Value&other)const;
    Value operator*(const double other)const;
    operator std::string()const;
    operator float()const;
    bool operator<(const Value&other)const;
    bool operator>(const Value&other)const;
    bool operator==(const Value&other)const;
    bool operator!=(const Value&other)const;
  protected:
    double m_myu;
  };

  typedef std::vector<Value> ValueVector;
  typedef std::vector<unsigned int>   IntVector;
};

#endif
