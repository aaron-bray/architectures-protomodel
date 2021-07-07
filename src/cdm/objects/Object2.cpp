/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "Object2.h"
#include <limits>
#include <cmath>

Object2::Object2()
{
  clear();
}

Object2::~Object2()
{
  clear();
}

void Object2::clear()
{
  m_Bar_mL_per_s = std::numeric_limits<double>::quiet_NaN();
}

bool Object2::hasBar_mL_per_s() const
{
  return !std::isnan(m_Bar_mL_per_s);
}
double Object2::getBar_mL_per_s() const
{
  return m_Bar_mL_per_s;
}
void Object2::setBar_mL_per_s(double d)
{
  m_Bar_mL_per_s = d;
}