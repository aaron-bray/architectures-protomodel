/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

#include "cdm/CommonDataModel.h"
#include "cdm/objects/Object1.h"
#include "cdm/objects/Object2.h"
#include <vector>

class Algorithm
{
protected:
  friend class CommonDataModelSerialization;
public:
  Algorithm();
  virtual ~Algorithm();

  virtual void clear();

  virtual bool serializeToString(std::string& output, eSerializationFormat m) const;
  virtual bool serializeToFile(const std::string& filename) const;
  virtual bool serializeFromString(const std::string& src, eSerializationFormat m);
  virtual bool serializeFromFile(const std::string& filename);

  bool hasObject1() const;
  Object1& getObject1();
  const Object1* getObject1() const;

  void clearObject2s();
  Object2& addObject2();
  const std::vector<Object2*>& getObject2s();
  const std::vector<const Object2*>& getObject2s() const;

  // Algorithms associated with this class
  void ComputeObject1();

protected:
  Object1* m_Object1;
  std::vector<Object2*> m_Object2s;
};