#include <iostream>
#include <cassert>
#include <SDL2/SDL.h>
#include "utils.hpp"

SDL_Window*   g_window   = nullptr;
SDL_Renderer* g_renderer = nullptr;

void init_sdl_and_window() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		assert(false);
	}

	int const window_w = 1000;
	int const window_h = 800;
	g_window = SDL_CreateWindow("When The Chess",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		window_w, window_h,
		SDL_WINDOW_RESIZABLE);

	g_renderer = SDL_CreateRenderer(g_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
}

/* Set to `false` to exit the game loop. */
bool gameloop_running = true;

void exit_game_loop() {
	gameloop_running = false;
}

void handle_events() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				exit_game_loop();
			break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						exit_game_loop();
					break;
				}
			break;
		}
	}
}

void draw_all() {
	SDL_SetRenderDrawColor(g_renderer, 54, 32, 96, 255);
	SDL_RenderClear(g_renderer);
	SDL_RenderPresent(g_renderer);
}

int main() {
	std::cout << "When The Chess - v0.0 indev or something" << std::endl;

	init_sdl_and_window();

	/* The game loop. */
	while (gameloop_running) {
		handle_events();
		draw_all();
	}

	return EXIT_SUCCESS;
}
