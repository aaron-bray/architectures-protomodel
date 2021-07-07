/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "cdm/algorithms/Algorithm.h"
#include "cdm/io/CommonDataModelSerialization.h"

Algorithm::Algorithm()
{
  m_Object1 = nullptr;
}

Algorithm::~Algorithm()
{
  clear();
}

void Algorithm::clear()
{
  SAFE_DELETE(m_Object1);
  clearObject2s();
}

bool Algorithm::serializeToString(std::string& output, eSerializationFormat m) const
{
  return CommonDataModelSerialization::serializeToString(*this, output, m);
}
bool Algorithm::serializeToFile(const std::string& filename) const
{
  return CommonDataModelSerialization::serializeToFile(*this, filename);
}
bool Algorithm::serializeFromString(const std::string& src, eSerializationFormat m)
{
  return CommonDataModelSerialization::serializeFromString(src, *this, m);
}
bool Algorithm::serializeFromFile(const std::string& filename)
{
  return CommonDataModelSerialization::serializeFromFile(filename, *this);
}

bool Algorithm::hasObject1() const
{
  return m_Object1 != nullptr;
}
Object1& Algorithm::getObject1()
{
  if (!hasObject1())
    m_Object1 = new Object1();
  return *m_Object1;
}
const Object1* Algorithm::getObject1() const
{
  return m_Object1;
}

void Algorithm::clearObject2s()
{
  DELETE_VECTOR(m_Object2s);
}
Object2& Algorithm::addObject2()
{
  Object2* o = new Object2();
  m_Object2s.push_back(o);
  return *o;
}
const std::vector<Object2*>& Algorithm::getObject2s()
{
  return m_Object2s;
}
const std::vector<const Object2*>& Algorithm::getObject2s() const
{
  return *((std::vector<const Object2*>*) &m_Object2s);
}

void Algorithm::ComputeObject1()
{
  double sum = 0;
  for (Object2* o : m_Object2s)
    if(o->hasBar_mL_per_s())
      sum += o->getBar_mL_per_s();

  getObject1().setFoo_mg_per_mL(sum);
}
