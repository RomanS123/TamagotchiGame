#include <TamagotchiGame/DatabaseConnection.hpp>
#include <TamagotchiGame/FileManager.hpp>
#include <TamagotchiGame/Pet.hpp>
#include <TamagotchiGame/StatesController.hpp>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <pqxx/pqxx>
#include <string>

std::map<std::string, int> Pet::fields_;

template <typename Container>
void UpdateField(Container& container, Container& residues,
                 std::string field_name, int change) {
  residues[field_name] = container[field_name] + change;
  if (container[field_name] + change >= 0) {
    container[field_name] += change;
  }
}

Pet::Pet() {
  RetrieveStats();
  std::map<std::string, int> residues;

  auto unix_time = std::time(nullptr);
  auto diff = (unix_time - fields_["last_login"]) / 60 / 10;

  UpdateField(fields_, residues, "food", -diff);
  UpdateField(fields_, residues, "happiness", -diff / 2);
  UpdateField(fields_, residues, "sleep", -diff);

  int min = std::min<int>(
      {residues["food"], residues["happiness"], residues["sleep"]});

  if (min <= 0) {
    fields_["hp"] += min;
  }
  UpdateStats();
}

void Pet::UpdateStats() {
  auto json = FileManager::ReadJson("../src/files/user.json");

  DatabaseConnection connection;
  connection.SetConnection();
  auto unix_time = std::time(nullptr);

  uint64_t user_id = json["user_id"].asUInt64();

  connection.Query("UPDATE users SET coins=" + std::to_string(fields_["coins"]) 
		  			+", food=" + std::to_string(fields_["food"]) +
                   ", happiness=" + std::to_string(fields_["happiness"]) +
                   ", hp=" + std::to_string(fields_["hp"]) +
                   ", sleep=" + std::to_string(fields_["sleep"]) +
                   ", state=" + std::to_string(fields_["state"]) +
                   ",last_login=" + std::to_string(unix_time) + " WHERE id=" + std::to_string(user_id));

  StatesController::GetInstance()->Update(this);
}

void Pet::RetrieveStats() {
  auto json = FileManager::ReadJson("../src/files/user.json");

  DatabaseConnection connection;
  connection.SetConnection();
  auto unix_time = std::time(nullptr);

  uint64_t user_id = json["user_id"].asUInt64();

  auto res = connection.Query(
      "SELECT coins, food, happiness, hp, sleep, state, last_login FROM users WHERE id=" +
      std::to_string(user_id));

  for (const auto& row : res) {
    for (uint32_t i = 0; i < row.size(); ++i) {
      fields_[res.column_name(i)] = std::atoi(row[i].c_str());
    }
  }
}

int Pet::GetStat(const std::string& stat_name) {
	return fields_[stat_name];
}

void Pet::SetStat(const std::string& stat_name, int value) {
	fields_[stat_name] = value;
}

void Pet::Feed(const std::string& what) {
	auto inventory = FileManager::ReadJson("../src/files/inventory.json");
	auto shop = FileManager::ReadJson("../src/files/shop.json");

	if(inventory.isMember(what) && inventory[what]["count"] > 0) {
		inventory[what]["count"] = Json::Value(inventory[what]["count"].asInt() - 1);
		fields_["food"] += shop[what]["richness"].asInt();
	}else{
		std::cout << "You do not have a " + what << "\n";
	}
	FileManager::WriteJson("../src/files/inventory.json", inventory);
	UpdateStats();
	
	StatesController::GetInstance()->Update(this);
}
