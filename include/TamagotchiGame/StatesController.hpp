#include <unordered_map>
#include <functional>
#include <concepts>

class StatesObserver {
	std::unordered_map<void*, std::function<void()>> mapping_;
	
	void AddAction(void* object, std::function<void()> action);

	//accepts multiple handlers
	template<std::invocable... Args>
	void AddAction(void* object, Args... args);
	
};
