#include <iostream>
#include <TamagotchiGame/FileManager.hpp>
#include <TamagotchiGame/DatabaseConnection.hpp>
#include <TamagotchiGame/StatesController.hpp>
#include <TamagotchiGame/Pet.hpp>
#include <TamagotchiGame/Shop.hpp>
#include <TamagotchiGame/BarsComponent.hpp>
#include <TamagotchiGame/PetComponent.hpp>
#include <TamagotchiGame/ItemComponent.hpp>
#include <DisplayLib/Window.hpp>
#include <DisplayLib/ComponentBuilder.hpp>
#include <pqxx/pqxx>
#include <ctime>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

void clearConsole() {
    // This is system dependent. For Windows use "cls", for Unix-based systems use "clear"
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void printCommands() {
    std::cout << "Commands:" << "\n";
    std::cout << "switch (main, shop, bed)" << "\n";
    std::cout << "buy (item_name)" << "\n";
    std::cout << "feed (item_name)" << "\n";
}

// Function to split input into command and arguments
std::vector<std::string> splitCommand(const std::string& command) {
    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

auto SwitchTo(const std::string& to) {
	Window<RendererASCII> window(40, 25);
	StatesController::GetInstance()->Clear();
	if(to == "main" || to == "bed") {
		auto bars = ComponentBuilder<BarsComponent<RendererASCII>>().SetPosition(1, 0).SetSize(40, 5).Build();
		auto pet = ComponentBuilder<PetComponent<RendererASCII>>().SetPosition(1, 10).SetSize(40, 20).Build();
  		window.AddComponent("bars", bars);
		window.AddComponent("pet", pet);
		window.Render("bars", nullptr);
		window.Render("pet", nullptr);
	} else {
		auto shop = FileManager::ReadJson("../src/files/shop.json");

		uint32_t count = 0;
		for(auto& item : shop.getMemberNames()) {
			auto comp = ComponentBuilder<ItemComponent<RendererASCII>>().SetPosition(2 + (count % 2)*16, (count / 2) * 14).SetSize(15, 12).Build();
			comp->SetItem(std::move(item));
			window.AddComponent(std::move(item), comp);
			//window.Render(std::move(item), nullptr);
			++count;
		}
	}
	return window;
}

int main() {
    auto json = FileManager::ReadJson("../src/files/user.json");

	DatabaseConnection connection;
	connection.SetConnection();
	auto unix_time = std::time(nullptr);
	if (!json.isMember("user_id")){
		//we need to create user in db
		uint64_t user_id = json["user_id"].asUInt64();
		connection.Query("INSERT INTO users (coins, food, happiness, hp, sleep, state, last_login) VALUES (100, 100, 100, 100, 100, 0," + std::to_string(unix_time) + ")");
		
		auto res = connection.Query("SELECT id FROM users WHERE last_login=" + std::to_string(unix_time));
		user_id = std::atoi(res[0][0].c_str());
		json["user_id"] = Json::Value(user_id);
		
		FileManager::WriteJson("../src/files/user.json", json);

		std::cout << "no user, create one";
	}
	
	Pet pet;
	Shop shop;

	std::string input;
	std::string current_location = "main";
    while (true) {
        clearConsole();
		SwitchTo(current_location);
        printCommands();

        std::cout << "Enter a command: ";
        std::getline(std::cin, input);

        // Split the input into command and arguments
        std::vector<std::string> commandParts = splitCommand(input);
        if (commandParts.empty()) {
            continue; // No input, continue to the next iteration
        }

        // Get the command
        std::string command = commandParts[0];

        // Process the command
        if (command == "exit") {
            break; // Exit the loop and program if the command is "exit"
        } else if (command == "switch") {
            if (commandParts.size() > 1) {
                std::string place = commandParts[1];
                std::cout << "Switching to " << place << "...\n";
                // Handle switch command with mode argument
            	if(place == "bed") {
					pet.SetStat("state", 1);
				}else if(place == "main") {
					pet.SetStat("state", 0);
				}else {
					
				}
				current_location = place;
				pet.UpdateStats();
			} else {
                std::cout << "Error: 'switch' command requires an argument.\n";
            }
        } else if (command == "buy") {
            if (commandParts.size() > 1) {
                std::string item_name = commandParts[1];
                std::cout << "Buying " << item_name << "...\n";
                shop.Buy(item_name);
				// Handle buy command with item_name argument
            } else {
                std::cout << "Error: 'buy' command requires an argument.\n";
            }
        } else if (command == "feed") {
            if (commandParts.size() > 1) {
                std::string item_name = commandParts[1];
                pet.Feed(item_name);
				// Handle feed command with item_name argument
            } else {
                std::cout << "Error: 'feed' command requires an argument.\n";
            }
        } else {
            std::cout << "Unknown command!\n";
        }

        // Pause to let the user see the result before clearing the screen again
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}
