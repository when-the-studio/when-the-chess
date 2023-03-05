#include <cassert>
#include <SDL2/SDL.h>
#include "renderer.hpp"
#include "lboard.hpp"

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

	void draw_all(logical::Board const& board) {
		SDL_SetRenderDrawColor(s_renderer, 54, 32, 96, 255);
		SDL_RenderClear(s_renderer);

		for (CoordsInt coords : board.rect_that_contains_all_the_tiles()) {
			/* Placeholder rendering of tiles. */
			SDL_SetRenderDrawColor(s_renderer,
				(coords.y * 100) % 256, (coords.x * 100) % 256, 0, 255);
			SDL_Rect rect{coords.x * 30, coords.y * 30, 30, 30};
			SDL_RenderFillRect(s_renderer, &rect);
		}

		SDL_RenderPresent(s_renderer);
	}
}
