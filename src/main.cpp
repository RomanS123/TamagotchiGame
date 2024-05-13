#include <iostream>
//#include <jsoncpp/jsoncpp.cpp>
#include <TamagotchiGame/FileManager.hpp>
#include <TamagotchiGame/DatabaseConnection.hpp>
#include <pqxx/pqxx>

int main() {
	auto json = FileManager::ReadJson("../src/files/user.json");
	uint64_t user_id = 0;
	std::cout << json;	

	if (json.isMember("user_id")){
		user_id = json["user_id"].asUInt64();
	}else{
		//we need to create user in db
		std::cout << "no user, xuy";
	}
} 
