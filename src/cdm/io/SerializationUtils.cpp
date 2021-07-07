/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include <google/protobuf/text_format.h>
#include <google/protobuf/util/json_util.h>
#include "io/SerializationUtils.h"

#include <sstream>
#include <fstream>
#include <filesystem>

bool IsJSONFile(const std::string& filename)
{
  size_t ext = filename.find_last_of(".");
  return filename.substr(ext) == ".json";
}

bool CreateFilePath(const std::string& filenamePath)
{
  // Separate path from file, and create the path
  auto const sep = filenamePath.find_last_of("\\/");
  if (sep != std::string::npos && sep > 0)
    return std::filesystem::create_directory(filenamePath.substr(0, sep));
  return true; // Nothing to do... 
}

bool WriteFile(const std::string& content, const std::string& filename)
{
  if (!CreateFilePath(filename))
    return false;
  std::ofstream ascii_ostream(filename, std::ios::out | std::ios::trunc);
  ascii_ostream << content;
  ascii_ostream.flush();
  ascii_ostream.close();
  return true;
}

bool ReadFile(const std::string& filename, std::string& content)
{
  if (!std::filesystem::exists(filename))
    return false;

  std::ifstream input(filename);
  if (!input.is_open())
    return false;
  std::string buff((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
  input.close();
  content = buff;
  return true;
}

void SerializationUtils::protobufLogHandler(google::protobuf::LogLevel level, const char* filename, int line, const std::string& message)
{
  switch (level)
  {
  case google::protobuf::LOGLEVEL_INFO:
    std::cout << "[INFO] " << filename << "::" << line << " : " << message;
    break;
  case google::protobuf::LOGLEVEL_WARNING:
    std::cout << "[WARN] " << filename << "::" << line << " : " << message;
    break;
  case google::protobuf::LOGLEVEL_ERROR:
    std::cout << "[ERROR] " << filename << "::" << line << " : " << message;
    break;
  case google::protobuf::LOGLEVEL_FATAL:
    std::cout << "[FATAL] " << filename << "::" << line << " : " << message;
    break;
  }
}

bool SerializationUtils::serializeFromFile(const std::string& filename, google::protobuf::Message& dst)
{
  if (!std::filesystem::exists(filename))
    return false;
  if (IsJSONFile(filename))
  {
    std::string content;
    if (!ReadFile(filename, content))
      return false;
    if (!serializeFromString(content, dst, eSerializationFormat::JSON))
      return false;
    return true;
  }
  std::ifstream input(filename, std::ios::binary);
  if (!input.is_open())
    return false;
  google::protobuf::SetLogHandler(static_cast<google::protobuf::LogHandler*>(SerializationUtils::protobufLogHandler));
  bool b = dst.ParseFromIstream(&input);
  input.close();
  return b;
}

bool SerializationUtils::serializeToFile(const google::protobuf::Message& src, const std::string& filename)
{
  if (IsJSONFile(filename))
  {
    std::string content;
    if (!serializeToString(src, content, eSerializationFormat::JSON))
      return false;
    return WriteFile(content, filename);
  }
  if (!CreateFilePath(filename))
    return false;
  google::protobuf::SetLogHandler(static_cast<google::protobuf::LogHandler*>(SerializationUtils::protobufLogHandler));
  std::ofstream output(filename, std::ios::binary);
  bool b = src.SerializeToOstream(&output);
  output.close();
  return b;
}

bool SerializationUtils::serializeFromString(const std::string& src, google::protobuf::Message& dst, eSerializationFormat m)
{
  bool ret = true;
  if (m == eSerializationFormat::JSON)
  {
    google::protobuf::SetLogHandler(static_cast<google::protobuf::LogHandler*>(SerializationUtils::protobufLogHandler));
    google::protobuf::util::JsonParseOptions opts;
    google::protobuf::util::Status stat = google::protobuf::util::JsonStringToMessage(src, &dst, opts);
    if (!stat.ok())
    {
      std::cerr << stat.ToString() << std::endl;
      ret = false;
    }
  }
  else
  {
    ret = dst.ParseFromString(src);
  }
  return ret;
}

bool SerializationUtils::serializeToString(const google::protobuf::Message& src, std::string& output, eSerializationFormat m)
{
  bool ret = true;
  if (m == eSerializationFormat::JSON)
  {
    google::protobuf::SetLogHandler(static_cast<google::protobuf::LogHandler*>(SerializationUtils::protobufLogHandler));
    google::protobuf::util::JsonPrintOptions opts;
    opts.add_whitespace = true;
    opts.preserve_proto_field_names = true;
    //bool ret = google::protobuf::TextFormat::PrintToString(src, &output);
    ret =  google::protobuf::util::MessageToJsonString(src, &output, opts).ok();
  }
  else
  {
    ret = src.SerializeToString(&output);
  }
  return ret;
}
