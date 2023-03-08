#include <cassert>
#include <array>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderer.hpp"
#include "lboard.hpp"

namespace renderer {
	static SDL_Window*   s_window   = nullptr;
	static SDL_Renderer* s_renderer = nullptr;
	/* Test image assets. */
	static std::array<SDL_Texture*, 12> s_test_pieces_sprites{nullptr};

	static void load_images() {
		#if 0
			/* TODO: Enable this piece of code when we get PNG image assets to load. */
			if (IMG_Init(IMG_INIT_PNG) == 0) {
				assert(false);
			}
		#endif
		
		/* Test loading the image assets. */
		std::array<char const*, 12> piece_image_asset_file_paths{
			"../assets/images/Chess_plt45.svg",
			"../assets/images/Chess_rlt45.svg",
			"../assets/images/Chess_nlt45.svg",
			"../assets/images/Chess_blt45.svg",
			"../assets/images/Chess_qlt45.svg",
			"../assets/images/Chess_klt45.svg",
			"../assets/images/Chess_pdt45.svg",
			"../assets/images/Chess_rdt45.svg",
			"../assets/images/Chess_ndt45.svg",
			"../assets/images/Chess_bdt45.svg",
			"../assets/images/Chess_qdt45.svg",
			"../assets/images/Chess_kdt45.svg",
		};
		for (std::size_t i = 0; i < piece_image_asset_file_paths.size(); i++) {
			char const* file_path = piece_image_asset_file_paths[i];
			SDL_Surface* surface = IMG_Load(file_path);
			assert(surface != nullptr);
			s_test_pieces_sprites[i] = SDL_CreateTextureFromSurface(s_renderer, surface);
			SDL_FreeSurface(surface);
			assert(s_test_pieces_sprites[i] != nullptr);
		}

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
		
		/* Test rendering of the image assets. */
		for (std::size_t i = 0; i < s_test_pieces_sprites.size(); i++) {
			SDL_Rect rect{100 + static_cast<int>(i) * 45, 100, 45, 45};
			SDL_RenderCopy(s_renderer, s_test_pieces_sprites[i], NULL, &rect);
		}

		SDL_RenderPresent(s_renderer);
	}
}
