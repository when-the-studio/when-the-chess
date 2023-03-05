#ifndef HEADER_WHEN_THE_CHESS_RENDERER_
#define HEADER_WHEN_THE_CHESS_RENDERER_

namespace logical { class Board; }

/* Encapsulates the rendering. */
namespace renderer {
	/* Creates the window and renderer,
	 * must be called at some point during initialization. */
	void init();

	/* Draw the whole window content for a frame.
	 * If VSync works then it blocks until screen refresh (at a rate that might
	 * depend on the system and the screen). */
	void draw_all(logical::Board const& board);
}

#endif /* HEADER_WHEN_THE_CHESS_RENDERER_ */
