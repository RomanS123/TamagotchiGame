#include <DisplayLib/Component.hpp>
#include <TamagotchiGame/FileManager.hpp>
#include <pqxx/pqxx>

template <typename Rend>
class PetComponent;

template <>
class PetComponent<RendererASCII> : public Component<RendererASCII> {
 public:
  void render(void* callee, RendererASCII& rend) override {
  	rend.SetComponent("pet");
  	
	auto json = FileManager::ReadJson("../src/files/pets.json");
	json = json["pou"];
	
	std::string state;
	if(Pet::GetStat("state") == 0) {	
		state = "active";
	}else{
		state = "sleeping";
	}

	auto art = json["states"][state]["art"];
	for(uint32_t i = 0; i < art.size(); ++i) {
		rend << art[i].asString();	
	}

	rend.Draw();
  }
};
