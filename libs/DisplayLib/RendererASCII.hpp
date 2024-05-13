#include "Window.hpp"
#include <string>
#include <cstdint>
#include <vector>
#include <unordered_map>

class RendererASCII;

class RendererASCII {
	public:
		/*
		this method used to specify with what component
	 	you are working, for example when you want to fill
	 	component with some contents 
		*/
		void SetComponent(std::string&&, int64_t new_position = -1);

		RendererASCII& operator<<(std::string);
	private:
		friend class Window<RendererASCII>;
		
		/* user can't create any Renderer
		 * separately from Window that it will ren			der
		*/
		RendererASCII(Window<RendererASCII>* window): window_(window) {
			std::string empty(window->GetWidth(), ' ');
			std::cout << "[" << empty << "]";
			state_.resize(window->GetHeight(), empty);
		}
	private:
		Window<RendererASCII>* window_;
		Component<RendererASCII>* current_component_ = nullptr;
		std::vector<std::string> state_;
		std::unordered_map<Component<RendererASCII>*, int> current_positions_;
};
