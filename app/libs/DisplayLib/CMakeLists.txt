#name of our library
project(lib)

add_library(DisplayLib SHARED RendererASCII.cpp Window.hpp Component.hpp)

set_target_properties(DisplayLib PROPERTIES 
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED TRUE
	)

#says that every target linked to Addition library
#has to include directory Tamagotchigame/libs/DisplayLib, but Addition itself doesn't
target_include_directories(DisplayLib
	                           INTERFACE ${lib_SOURCE_DIR}
)

