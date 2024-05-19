#include <TamagotchiGame/Shop.hpp>
#include <TamagotchiGame/FileManager.hpp>
#include <TamagotchiGame/StatesController.hpp>
#include <TamagotchiGame/Pet.hpp>
#include <TamagotchiGame/DatabaseConnection.hpp>
#include <jsoncpp/jsoncpp.cpp>

#define DATA_PATH "../src/files/"

void Shop::Buy(std::string item) {
	auto items = FileManager::ReadJson(std::string(DATA_PATH) + "shop.json");
	auto inventory = FileManager::ReadJson(std::string(DATA_PATH) + "inventory.json");
	
	if(!items.isMember(item)) {
		std::cout << "There is no item called \"" + item + "\"";
		return;
	}
	
	if(items[item]["cost"].asInt() > Pet::GetStat("coins")) {
		std::cout << "you have no money";
		return;
	}
	
	inventory[item]["count"] = Json::Value(inventory[item]["count"].asInt() + 1);

	Pet::SetStat("coins", Pet::GetStat("coins") - items[item]["cost"].asInt());
	FileManager::WriteJson("../src/files/inventory.json", inventory);

  	auto json = FileManager::ReadJson("../src/files/user.json");
	
	DatabaseConnection connection;
  	connection.SetConnection();
  	auto unix_time = std::time(nullptr);

  	uint64_t user_id = json["user_id"].asUInt64();
	
  	connection.Query("UPDATE users SET coins=" + std::to_string(Pet::GetStat("coins") - items[item]["cost"].asInt()) + 
			",last_login=" + std::to_string(unix_time) + " WHERE id="+std::to_string(user_id));

  	StatesController::GetInstance()->Update(this);
}
