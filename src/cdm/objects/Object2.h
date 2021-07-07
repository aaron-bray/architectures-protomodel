/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

class Object2
{
public:
  Object2();
  virtual ~Object2();

  virtual void clear();

  bool hasBar_mL_per_s() const;
  double getBar_mL_per_s() const;
  void setBar_mL_per_s(double d);

protected:
  double m_Bar_mL_per_s;
};