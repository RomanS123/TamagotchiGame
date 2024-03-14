#include <Component.hpp>
#include <string>

class RendererASCII {
	std::reference_wrapper<unordered_map<std::string, Component*>> mapping_;
	Component* current_component;

	/*
	this method used to specify with what component
	 you are working, for example when you want to fill
	 component with some contents 
	*/
	void SetComponent(std::string);

	RendererASCII& operator<<(std::string);
};
