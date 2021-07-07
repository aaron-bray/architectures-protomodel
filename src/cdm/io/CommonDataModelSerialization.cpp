/* Distributed under the Apache Licen, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "cdm/io/CommonDataModelSerialization.h"
#include "cdm/io/SerializationUtils.h"
#include "CommonDataModel.pb.h"

#include "cdm/algorithms/Algorithm.h"


void CommonDataModelSerialization::load(const CDM_BIND::AlgorithmData& src, Algorithm& dst)
{
  dst.clear();
  CommonDataModelSerialization::serialize(src, dst);
}
void CommonDataModelSerialization::serialize(const CDM_BIND::AlgorithmData& src, Algorithm& dst)
{
  if (src.has_object1())
    serialize(src.object1(), dst.getObject1());

  for (int i = 0; i < src.object2_size(); i++)
  {
    Object2& o = dst.addObject2();
    serialize(src.object2()[i], o);
  }
}

CDM_BIND::AlgorithmData* CommonDataModelSerialization::unload(const Algorithm& src)
{
  CDM_BIND::AlgorithmData* dst = new CDM_BIND::AlgorithmData();
  CommonDataModelSerialization::serialize(src, *dst);
  return dst;
}
void CommonDataModelSerialization::serialize(const Algorithm& src, CDM_BIND::AlgorithmData& dst)
{
  if (src.hasObject1())
    serialize(*src.getObject1(), *dst.mutable_object1());

  for (const Object2* o : src.getObject2s())
  {
    auto d = dst.add_object2();
    serialize(*o, *d);
  }
}

void CommonDataModelSerialization::load(const CDM_BIND::Object1Data& src, Object1& dst)
{
  dst.clear();
  CommonDataModelSerialization::serialize(src, dst);
}
void CommonDataModelSerialization::serialize(const CDM_BIND::Object1Data& src, Object1& dst)
{
  dst.setFoo_mg_per_mL(src.foo_mg_per_ml());
}

CDM_BIND::Object1Data* CommonDataModelSerialization::unload(const Object1& src)
{
  CDM_BIND::Object1Data* dst = new CDM_BIND::Object1Data();
  CommonDataModelSerialization::serialize(src, *dst);
  return dst;
}
void CommonDataModelSerialization::serialize(const Object1& src, CDM_BIND::Object1Data& dst)
{
  if (src.hasFoo_mg_per_mL())
    dst.set_foo_mg_per_ml(src.getFoo_mg_per_mL());
}

void CommonDataModelSerialization::load(const CDM_BIND::Object2Data& src, Object2& dst)
{
  dst.clear();
  CommonDataModelSerialization::serialize(src, dst);
}
void CommonDataModelSerialization::serialize(const CDM_BIND::Object2Data& src, Object2& dst)
{
  dst.setBar_mL_per_s(src.bar_ml_per_s());
}

CDM_BIND::Object2Data* CommonDataModelSerialization::unload(const Object2& src)
{
  CDM_BIND::Object2Data* dst = new CDM_BIND::Object2Data();
  CommonDataModelSerialization::serialize(src, *dst);
  return dst;
}
void CommonDataModelSerialization::serialize(const Object2& src, CDM_BIND::Object2Data& dst)
{
  if (src.hasBar_mL_per_s())
    dst.set_bar_ml_per_s(src.getBar_mL_per_s());
}

bool CommonDataModelSerialization::serializeToString(const Algorithm& src, std::string& output, eSerializationFormat m)
{
  CDM_BIND::AlgorithmData data;
  CommonDataModelSerialization::serialize(src, data);
  return SerializationUtils::serializeToString(data, output, m);
}
bool CommonDataModelSerialization::serializeToFile(const Algorithm& src, const std::string& filename)
{
  CDM_BIND::AlgorithmData data;
  CommonDataModelSerialization::serialize(src, data);
  return SerializationUtils::serializeToFile(data, filename);
}

bool CommonDataModelSerialization::serializeFromString(const std::string& src, Algorithm& dst, eSerializationFormat m)
{
  CDM_BIND::AlgorithmData data;
  if (!SerializationUtils::serializeFromString(src, data, m))
    return false;
  CommonDataModelSerialization::load(data, dst);
  return true;
}
bool CommonDataModelSerialization::serializeFromFile(const std::string& filename, Algorithm& dst)
{
  CDM_BIND::AlgorithmData data;
  if (!SerializationUtils::serializeFromFile(filename, data))
    return false;
  CommonDataModelSerialization::load(data, dst);
  return true;
}
