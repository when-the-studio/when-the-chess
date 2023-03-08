cmake_minimum_required(VERSION 3.16)

project(
	"When the chess"
	VERSION
	0.1
	LANGUAGES
	CXX
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
	"${CMAKE_SOURCE_DIR}/cmake/"
)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_compile_options(
	-Wall
	-Wextra
	-pedantic
	-O2
	-std=c++20
)
add_executable(wtc
	${SRC_FILES}
)


target_include_directories(wtc 
	PRIVATE
	${PROJECT_SOURCE_DIR}/include
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(wtc ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

set_target_properties(wtc 
	PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin
)
