#include <unordered_map>
#include <string>
#include "Component.hpp"
#include <cstdint>
#pragma once

template<typename Renderer>
class Window {
	public:
		
	Window(uint32_t width, uint32_t height): width_(width), height_(height), renderer_(this) {}

	//calls render() method in Component derived classes
	void Render(std::string&& component_name, void* callee);

	void AddComponent(std::string&& component_name, Component<Renderer>* component);

	uint32_t GetWidth() const {
		return width_;
	}

	uint32_t GetHeight() const {
		return height_;
	}

	Component<Renderer>* GetComponent(std::string&& component_name);
	
	~Window() {
		for(auto& [name, ptr] : mapping_) {
			delete ptr;
		}
	}

	private:
	uint32_t width_;
	uint32_t height_;
	std::unordered_map<std::string, Component<Renderer>*> mapping_;
	Renderer renderer_;
};

template<typename Renderer>
void Window<Renderer>::Render(std::string&& component_name, void* callee) {
	mapping_[component_name]->render(callee, renderer_);
}

template<typename Renderer>
void Window<Renderer>::AddComponent(std::string&& component_name, Component<Renderer>* component) {
	mapping_[component_name] = component;
}

template<typename Renderer>
Component<Renderer>* Window<Renderer>::GetComponent(std::string&& component_name) {
	return mapping_[component_name];
}

