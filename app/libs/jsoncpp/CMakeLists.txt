project(jsoncpp)

add_library(jsoncpp STATIC jsoncpp.cpp)

target_include_directories(jsoncpp
	PUBLIC json/
)
