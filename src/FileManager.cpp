#include <TamagotchiGame/FileManager.hpp>
#include <fstream>
#include <jsoncpp/jsoncpp.cpp>
#include <string>

class FileManager {
  static Json::Value ReadJson(std::string filename) {
    std::ifstream file(filename, std::ifstream::binary);
    Json::Value json;
    file >> json;
    return json;
  }

  static void WriteJson(std::string filename, Json::Value json) {
    std::ofstream file;
    file.open(filename);
    auto writer = GetJsonWriter();
    writer.write(json, &file);
  }
};
