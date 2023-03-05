#include <cassert>
#include "gameloop.hpp"
#include "renderer.hpp"
#include "events.hpp"

namespace gameloop {
	static bool gameloop_running = false;

	void loop() {
		gameloop_running = true;
		while (gameloop_running) {
			handle_events();
			renderer::draw_all();
		}
	}

	void exit() {
		assert(gameloop_running
			/* It makes no sense to exit from the game loop when it is not running. */);
		gameloop_running = false;
	}
}
