cmake_minimum_required(VERSION 3.19)
project(TamagotchiGame)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_custom_target(CreateNecessaryFiles
	COMMAND python3 ${CMAKE_SOURCE_DIR}/src/create_files.py
	  #WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src
)

#include DisplayLib to build it accordingly to its cmakelists file(shared lib)
add_subdirectory(libs/DisplayLib)
add_subdirectory(libs/jsoncpp)
add_subdirectory(libs/libpqxx)


file(GLOB source_files CONFIGURE_DEPENDS "src/*.cpp")

add_executable(main ${source_files})
#add_executable(main src/FileManager.cpp src/main.cpp)  # Add them to the executable
add_dependencies(main CreateNecessaryFiles)

target_include_directories(main 
	PUBLIC ${CMAKE_SOURCE_DIR}/libs
	PUBLIC ${CMAKE_SOURCE_DIR}/include
	)

#target_include_directories(Impl 
#	PUBLIC ${CMAKE_SOURCE_DIR}/libs
#	PUBLIC ${CMAKE_SOURCE_DIR}/include
#)
target_link_libraries(main PUBLIC DisplayLib jsoncpp pqxx)
