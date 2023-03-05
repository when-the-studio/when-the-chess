cmake_minimum_required(VERSION 3.16)

project(
    "When the chess"
    VERSION
    0.1
    LANGUAGES
    CXX
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
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(wtc ${SDL2_LIBRARIES})

set_target_properties(wtc 
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin
)
