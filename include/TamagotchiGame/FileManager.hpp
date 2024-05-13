#include <fstream>
#include <jsoncpp/json/json.h>
#include <string>
#pragma once

class FileManager {
 public:
  static Json::Value ReadJson(std::string filename);

  static void WriteJson(std::string filename, Json::Value json);
};
