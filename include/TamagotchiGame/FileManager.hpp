#include <string>
#include <libs/jsoncpp/jsoncpp.cpp>
#include <fstream>

Json::StreamWriter GetJsonWriter() {
	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "	";
	
	return Json::StreamWriter(builder);
}

class FileManager {
	static Json::Value ReadJson(std::string filename);

	static void WriteJson(std::string filename, Json::Value json);
};
