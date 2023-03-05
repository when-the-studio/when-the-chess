#include <SDL2/SDL.h>
#include "events.hpp"
#include "gameloop.hpp"

void handle_events() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				gameloop::exit();
			break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						gameloop::exit();
					break;
				}
			break;
		}
	}
}
