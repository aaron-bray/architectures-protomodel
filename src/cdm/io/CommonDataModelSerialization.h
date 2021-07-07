/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "CommonDataModel.h"

CDM_BIND_DECL(Algorithm)
CDM_BIND_DECL(Object1)
CDM_BIND_DECL(Object2)

class CommonDataModelSerialization
{
public:

  static void load(const CDM_BIND::AlgorithmData& src, Algorithm& dst);
  static CDM_BIND::AlgorithmData* unload(const Algorithm& src);
  static void serialize(const CDM_BIND::AlgorithmData& src, Algorithm& dst);
  static void serialize(const Algorithm& src, CDM_BIND::AlgorithmData& dst);

  static bool serializeToString(const Algorithm& src, std::string& output, eSerializationFormat m);
  static bool serializeToFile(const Algorithm& src, const std::string& filename);
  static bool serializeFromString(const std::string& src, Algorithm& dst, eSerializationFormat m);
  static bool serializeFromFile(const std::string& filename, Algorithm& dst);

  static void load(const CDM_BIND::Object1Data& src, Object1& dst);
  static CDM_BIND::Object1Data* unload(const Object1& src);
  static void serialize(const CDM_BIND::Object1Data& src, Object1& dst);
  static void serialize(const Object1& src, CDM_BIND::Object1Data& dst);

  static void load(const CDM_BIND::Object2Data& src, Object2& dst);
  static CDM_BIND::Object2Data* unload(const Object2& src);
  static void serialize(const CDM_BIND::Object2Data& src, Object2& dst);
  static void serialize(const Object2& src, CDM_BIND::Object2Data& dst);

};
