#ifndef HEADER_WHEN_THE_CHESS_GAMELOOP_
#define HEADER_WHEN_THE_CHESS_GAMELOOP_

/* Encapsulates the rendering. */
namespace gameloop {
	/* Main loop that handles events, rendering and all. */
	void loop();

	/* Calling this while the game loop is running will make it so that
	 * the game loop terminates (i.e. the `gameloop::loop()` call returns). */
	void exit();
}

#endif /* HEADER_WHEN_THE_CHESS_GAMELOOP_ */
