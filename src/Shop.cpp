#include <TamagotchiGame/Shop.hpp>
#include <TamagotchiGame/FileManager.hpp>
#include <jsoncpp/jsoncpp.cpp>

#define DATA_PATH "../src/files"

void Shop::Buy(std::string item) {
	auto items = FileManager::ReadJson(std::string(DATA_PATH) + "shop.json");
	auto stats = FileManager::ReadJson(std::string(DATA_PATH) + "stats.json");
	
	/*
	if(items[item]["price"] > stats["money"]) {
		state = "nomoney";
		return;
	}

	stats["money"] -= items[item]["price"];
	
	FileManager::WriteJson(std::string(DATA_PATH) + "stats.json", stats);

	auto inventory = FileManager::ReadJson(std::string(DATA_PATH) + "inventory.json");

	inventory[item]["count"] -= 1;
	*/
}
