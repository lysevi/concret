#include "value.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>
namespace fuzzy
{
  Value::Value():m_myu(-9999.9999)
  {}
  
  Value::Value(double myu)
  {
    if(myu>1.0)
      m_myu=1.0;
    else
      m_myu=myu;
    if(myu<0)
      throw std::logic_error("Value: myu must be>0");
  }

  Value::Value(const Value&other):m_myu(other.m_myu)
  {}

  Value Value::operator=(const Value&other)
  {
    m_myu=other.m_myu;
  }

  Value Value::operator+=(const Value&other)
  {
    m_myu+=other.m_myu;
  }

  double Value::myu()const
  {
    return m_myu;
  }

  Value Value::operator&&(const Value&other) const
  {
    if(m_myu<other.m_myu)
      return Value(*this);
    else
      return Value(other);
  }
  
  Value Value::operator||(const Value&other) const
  {
    if(m_myu>other.m_myu)
      return Value(*this);
    else
      return Value(other);
  }
  
  Value Value::operator!() const
  {
    return Value(1-m_myu);
  }
  
  Value Value::operator+(const Value&other) const
  {
    return Value(m_myu+other.m_myu);
  }
  
  Value Value::operator-(const Value&other) const
  {
    return Value(m_myu-other.m_myu);
  }
  
  Value Value::operator/(const Value&other) const
  {
    double value=other.m_myu;
    if(value==0)
      value+=0.0001;
    return Value(m_myu/value);
  }
  
  Value Value::operator*(const Value&other) const
  {
    return Value(m_myu*other.m_myu);
  }

  Value Value::operator*(const double other) const
  {
    return Value(m_myu*other);
  }

  Value::operator std::string() const
  {
    std::ostringstream ss;
    ss<<"~"<<m_myu<<"~";
    return ss.str();
  }

  Value::operator float()const
  {
    return static_cast<float>(m_myu);
  }
  bool Value::operator<(const Value&other)const
  {
    return m_myu<other.m_myu;
  }
  
  bool Value::operator>(const Value&other)const
  {
    return m_myu>other.m_myu;
  }
  
  bool Value::operator==(const Value&other)const
  {
    return m_myu==other.m_myu;
  }
  
  bool Value::operator!=(const Value&other)const
  {
    return m_myu!=other.m_myu;
  }

};
