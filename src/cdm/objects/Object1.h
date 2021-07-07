/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

class Object1
{
public:
  Object1();
  virtual ~Object1();

  virtual void clear();

  bool hasFoo_mg_per_mL() const;
  double getFoo_mg_per_mL() const;
  void setFoo_mg_per_mL(double d);

protected:
  double m_Foo_mg_per_mL;
};