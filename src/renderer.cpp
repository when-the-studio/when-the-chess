#include <cassert>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderer.hpp"

namespace renderer {
	static SDL_Window*   s_window      = nullptr;
	static SDL_Renderer* s_renderer    = nullptr;
	static SDL_Texture*  s_test_horsie = nullptr; /* Test image asset. */

	static void load_images() {
		#if 0
			/* TODO: Enable this piece of code when we get PNG image assets to load. */
			if (IMG_Init(IMG_INIT_PNG) == 0) {
				assert(false);
			}
		#endif
		
		/* Test loading of an image asset. */
		SDL_Surface* surface = IMG_Load("assets/images/Chess_nlt45.svg");
		assert(surface != nullptr);
		s_test_horsie = SDL_CreateTextureFromSurface(s_renderer, surface);
		SDL_FreeSurface(surface);
		assert(s_test_horsie != nullptr);

		IMG_Quit();
	}

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

		load_images();
	}

	void draw_all() {
		SDL_SetRenderDrawColor(s_renderer, 54, 32, 96, 255);
		SDL_RenderClear(s_renderer);

		/* Test rendering of an image asset. */
		SDL_Rect rect{100, 100, 45, 45};
		SDL_RenderCopy(s_renderer, s_test_horsie, NULL, &rect);

		SDL_RenderPresent(s_renderer);
	}
}
