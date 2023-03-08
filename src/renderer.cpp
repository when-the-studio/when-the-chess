#include <cassert>
#include <array>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderer.hpp"
#include "lboard.hpp"

Rgb::Rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b):
r{r}, g{g}, b{b} {}

namespace renderer {
	static SDL_Window*   s_window   = nullptr;
	static SDL_Renderer* s_renderer = nullptr;
	/* Test image assets. */
	static std::array<SDL_Texture*, 12> s_test_pieces_sprites{nullptr};

	static Rgb s_rgb_tile_dark {150, 100, 40};
	static Rgb s_rgb_tile_light{200, 140, 40};

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

	static SDL_Texture* piece_texture(logical::Piece piece) {
		return s_test_pieces_sprites[
			5 - static_cast<int>(piece.type) +
			(piece.color == logical::PlayerColor::WHITE ? 0 : 1)
		];
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

		/* Render the background of tiles. */
		for (CoordsInt coords : board.rect_that_contains_all_the_tiles()) {
			Rgb const& color = (coords.x + coords.y) % 2 == 0 ?
				s_rgb_tile_light : s_rgb_tile_dark;
			SDL_SetRenderDrawColor(s_renderer, color.r, color.g, color.b, 255);
			SDL_Rect rect{coords.x * 45, coords.y * 45, 45, 45};
			SDL_RenderFillRect(s_renderer, &rect);
		}

		/* Render the pieces. */
		for (CoordsInt coords : board.rect_that_contains_all_the_tiles()) {
			std::optional<logical::Piece> const& opt_piece = board.tile_at(coords).opt_piece;
			if (not opt_piece.has_value()) {
				continue;
			}
			logical::Piece const& piece = opt_piece.value();
			SDL_Rect rect{coords.x * 45, coords.y * 45, 45, 45};
			SDL_RenderCopy(s_renderer, piece_texture(piece), NULL, &rect);
		}

		SDL_RenderPresent(s_renderer);
	}
}
