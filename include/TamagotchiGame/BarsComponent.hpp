#include <DisplayLib/Component.hpp>
#include <DisplayLib/RendererASCII.hpp>
#include <pqxx/pqxx>
#include <string>

template <typename Rend>
class BarsComponent;

template <>
class BarsComponent<RendererASCII> : public Component<RendererASCII> {
 public:
  void render(void* callee, RendererASCII& rend) override {
  	rend.SetComponent("bars");
	std::string tmp;
	for(uint32_t i = 0; i < GetWidth(); ++i) {
		tmp.append("-");
	}
    rend << tmp;
	rend << "Coins: " + std::to_string(Pet::GetStat("coins"));
    rend << "HP: " + std::to_string(Pet::GetStat("hp")) + "/ 100  |  Sleep: " + std::to_string(Pet::GetStat("sleep")) + "/ 100";
    rend << "Food: " + std::to_string(Pet::GetStat("food")) + "/ 100  |  Happiness: " + std::to_string(Pet::GetStat("happiness")) + "/ 100";
	rend << tmp;
  	rend.Draw();
  }
};


