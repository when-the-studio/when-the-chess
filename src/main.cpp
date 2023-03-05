#include <iostream>
#include <cassert>
#include <SDL2/SDL.h>
#include "renderer.hpp"
#include "gameloop.hpp"

int main() {
	std::cout << "When The Chess - v0.0 indev or something" << std::endl;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		assert(false);
	}
	renderer::init();

	gameloop::loop();

	return EXIT_SUCCESS;
}
