#include <TamagotchiGame/FileManager.hpp>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <string>

auto GetJsonWriter() {
  Json::StreamWriterBuilder builder;
  builder["commentStyle"] = "None";
  builder["indentation"] = "	";

  std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
  return writer;
}

Json::Value FileManager::ReadJson(std::string filename) {
  std::ifstream file(filename, std::ifstream::binary);
  Json::Value json;
  file >> json;
  file.close();
  return json;
}

void FileManager::WriteJson(std::string filename, Json::Value json) {
  std::ofstream file;
  file.open(filename);
  auto writer = GetJsonWriter();
  writer->write(json, &file);
  file.close();
}
