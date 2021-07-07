/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include <vector>
#include <string>

enum class eSerializationFormat { JSON = 0, BINARY };

#define SAFE_DELETE(obj) {delete obj; obj=nullptr;}

#define SAFE_DELETE_ARRAY(ary) {delete [] ary; *ary=nullptr;}

template<class T>
inline void DELETE_VECTOR(std::vector<T>& vec)
{
  for (unsigned int i = 0; i < vec.size(); i++)
  {
    delete vec.at(i);
  }
  vec.clear();
}

#define CDM_BIND protomodel::cdm::bind
#define CDM_BIND_DECL(type) \
  class type;\
  namespace protomodel { namespace cdm { namespace bind { class type##Data; }}}
