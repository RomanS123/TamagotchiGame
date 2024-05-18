cmake_minimum_required(VERSION 3.19)
project(TamagotchiGame)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_custom_target(CreateNecessaryFiles
	COMMAND python3 ${CMAKE_SOURCE_DIR}/src/create_files.py
	  #WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src
)
add_custom_target(run_postgres
    COMMAND docker run -p 5432:5432 --name tamagotchi_db -e POSTGRES_PASSWORD=abc -v ${CMAKE_SOURCE_DIR}/docker/data:/var/lib/postgresql/data -v ${CMAKE_SOURCE_DIR}/docker/init-scripts:/docker-entrypoint-initdb.d -d postgres
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Starting PostgreSQL Docker container"
    VERBATIM
)

#include DisplayLib to build it accordingly to its cmakelists file(shared lib)
add_subdirectory(libs/DisplayLib)
add_subdirectory(libs/jsoncpp)
add_subdirectory(libs/libpqxx)


file(GLOB source_files CONFIGURE_DEPENDS "src/*.cpp")

add_executable(main ${source_files})
add_dependencies(main CreateNecessaryFiles)
add_dependencies(main run_postgres)

target_include_directories(main 
	PUBLIC ${CMAKE_SOURCE_DIR}/libs
	PUBLIC ${CMAKE_SOURCE_DIR}/include
	)

#target_include_directories(Impl 
#	PUBLIC ${CMAKE_SOURCE_DIR}/libs
#	PUBLIC ${CMAKE_SOURCE_DIR}/include
#)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

target_link_libraries(main PUBLIC DisplayLib jsoncpp pqxx)
