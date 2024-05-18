#include <DisplayLib/Component.hpp>
#include <pqxx/pqxx>
#include <string>

template <typename Rend>
class ItemComponent;

template <>
class ItemComponent<RendererASCII> : public Component<RendererASCII> {
	std::string item_; 
public:
	void SetItem(std::string item) {
		item_ = item;
	}
  void render(void* callee, RendererASCII& rend) override {  
	rend.SetComponent(std::move(item_));
	
	auto inventory = FileManager::ReadJson("../src/files/inventory.json");
	auto shop = FileManager::ReadJson("../src/files/shop.json");
	
	auto item = shop[item_];
	
	std::string tmp;
	for(uint32_t i = 0; i < GetWidth(); ++i) {
		tmp.append("-");
	}

	rend << tmp;
	
	for(uint32_t i = 0; i < item["art"].size(); ++i) {
		rend << "| " + std::string(item["art"][i].asCString()) + " |"; 
	}
	rend << std::string(GetWidth(), ' ');
	rend << "Price: " << std::to_string(item["cost"].asInt());
	rend << "Inventory: " << std::to_string(inventory[item_]["count"].asInt());
	rend << tmp;

	rend.Draw();
  }
};


