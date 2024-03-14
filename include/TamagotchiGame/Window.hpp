#include <unordered_map>
#include <Component.hpp>

template<typename Renderer>
class Window {
	std::unordered_map<std::string, Component*> mapping_;
	Renderer renderer;

	void Render(std::string component_name, void* callee);
}
