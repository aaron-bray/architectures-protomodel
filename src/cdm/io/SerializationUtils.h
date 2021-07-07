/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

#include "CommonDataModel.h"
#include <google/protobuf/message.h>

class SerializationUtils
{
public:

  static bool serializeFromFile(const std::string& filename, google::protobuf::Message& dst);
  static bool serializeToFile(const google::protobuf::Message& src, const std::string& filename);

  static bool serializeFromString(const std::string& src, google::protobuf::Message& dst, eSerializationFormat m);
  static bool serializeToString(const google::protobuf::Message& src, std::string& output, eSerializationFormat m);

  static void protobufLogHandler(google::protobuf::LogLevel level, const char* filename, int line, const std::string& message);


};