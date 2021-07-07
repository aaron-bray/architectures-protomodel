/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "cdm/objects/Object1.h"
#include <limits>
#include <cmath>

Object1::Object1()
{
  clear();
}

Object1::~Object1()
{
  clear();
}

void Object1::clear()
{
  m_Foo_mg_per_mL = std::numeric_limits<double>::quiet_NaN();
}

bool Object1::hasFoo_mg_per_mL() const
{
  return !std::isnan(m_Foo_mg_per_mL);
}
double Object1::getFoo_mg_per_mL() const
{
  return m_Foo_mg_per_mL;
}
void Object1::setFoo_mg_per_mL(double d)
{
  m_Foo_mg_per_mL = d;
}
