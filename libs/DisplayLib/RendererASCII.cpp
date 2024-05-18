#include "RendererASCII.hpp"
#include <cstdlib>
#pragma once

void RendererASCII::SetComponent(std::string&& component_name, int64_t new_position) {
	current_component_ = window_->GetComponent(std::move(component_name));
	if(new_position != -1) {
		current_positions_[current_component_] = new_position;
	}
}

void RendererASCII::Draw() {
	//std::cout << "\033[2J\033[1;1H";
	#ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif	
	
	for(auto& str : state_) {
		std::cout << str << "\n";
	}
}

RendererASCII& RendererASCII::operator<<(std::string content) {
	/*work in assumption that width and height in Window class	
	mean number of columns and rows respectively
	*/
	if(!current_positions_.contains(current_component_)) {
		current_positions_[current_component_] = current_component_->GetY();
	}

	auto component_x = current_component_->GetX();
	auto component_width = current_component_->GetWidth();
	auto& current_position = current_positions_[current_component_];
	
	state_[current_position].replace(component_x, component_width, content);

	++current_position;
	return *this;
}
