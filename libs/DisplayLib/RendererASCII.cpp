#include "RendererASCII.hpp"
#pragma once

void RendererASCII::SetComponent(std::string&& component_name, int64_t new_position) {
	current_component_ = window_->GetComponent(std::move(component_name));
	if(new_position != -1) {
		current_positions_[current_component_] = new_position;
	}
}

RendererASCII& RendererASCII::operator<<(std::string content) {
	/*work in assumption that width and height in Window class	
	mean number of columns and rows respectively
	*/
	if(!current_positions_.contains(current_component_)) {
		current_positions_[current_component_] = 0;
	}

	auto component_x = current_component_->GetX();
	auto component_width = current_component_->GetWidth();
	auto& current_position = current_positions_[current_component_];

	state_[current_position].assign(content, component_x, component_width);

	++current_position;
	return *this;
}
