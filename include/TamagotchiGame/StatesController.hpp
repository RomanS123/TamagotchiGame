#include <unordered_map>
#include <functional>
#include <concepts>
#include <TamagotchiGame/AbstractObserver.hpp>
#include <list>

class StatesController: public AbstractObserver {
	std::unordered_map<void*, std::list<std::function<void()>>> mapping_;
	static constexpr StatesController* instance_ = nullptr;
	
	StatesController() = default;

	public:
	static StatesController* GetInstance();

	void AddAction(void* object, std::function<void()> action);

	void Update(void* callee) override;
};
