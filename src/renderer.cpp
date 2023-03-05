#include <cassert>
#include <SDL2/SDL.h>
#include "renderer.hpp"

namespace renderer {
	static SDL_Window*   s_window   = nullptr;
	static SDL_Renderer* s_renderer = nullptr;

	void init() {
		assert(SDL_WasInit(SDL_INIT_VIDEO));

		int const window_w = 1000;
		int const window_h = 800;

		s_window = SDL_CreateWindow("When The Chess",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			window_w, window_h,
			SDL_WINDOW_RESIZABLE);
		assert(s_window != nullptr);

		s_renderer = SDL_CreateRenderer(s_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
		assert(s_renderer != nullptr);
	}

	void draw_all() {
		SDL_SetRenderDrawColor(s_renderer, 54, 32, 96, 255);
		SDL_RenderClear(s_renderer);
		SDL_RenderPresent(s_renderer);
	}
}
