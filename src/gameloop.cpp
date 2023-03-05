#include <cassert>
#include "gameloop.hpp"
#include "renderer.hpp"
#include "events.hpp"

namespace gameloop {
	static bool s_gameloop_running = false;

	void loop() {
		s_gameloop_running = true;
		while (s_gameloop_running) {
			handle_events();
			renderer::draw_all();
		}
	}

	void exit() {
		assert(s_gameloop_running
			/* It makes no sense to exit from the game loop when it is not running. */);
		s_gameloop_running = false;
	}
}
