#ifndef HEADER_WHEN_THE_CHESS_LBOARD_
#define HEADER_WHEN_THE_CHESS_LBOARD_

#include <cstdint>
#include <optional>
#include <vector>

/* Designate a tile in a 2D grid. */
class CoordsInt {
public:
	int x, y;

public:
	CoordsInt(int x, int y);
};

/* Dimentions (width and height) of a rectangle of tiles in a 2D grid. */
class CoordsIntRectDims {
public:
	int w, h;

public:
	CoordsIntRectDims(int w, int h);
};

/* Everything in the `logical` namespace is purely about board states considered logically,
 * so that a logical board can be copied and used by the AI to think about hypothetical
 * moves and hypothetical board states in a fast and light weight way, with no side effects.
 * For example, nothing in there should have anything to do with renderig. */
namespace logical {
	enum class PlayerColor: std::int8_t {
		WHITE, BLACK
	};

	class Piece {
	public:
		enum class Type: std::int8_t {
			KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN
		};

	public:
		Type type;
		PlayerColor color;
	};

	class Tile {
	public:
		std::optional<Piece> opt_piece;
	};

	class Board {
	private:
		/* The tiles here are supposed to be squares arranged on a classic 2D grid.
		 * It has a rectangle (of dimentions specified by `dims`) of potential tiles
		 * so that it has some freedom in its possible shapes (although the tiles
		 * should not be too far away from eachother as this would waste a lot of memory). */
		std::vector<std::optional<Tile>> tile_rectangular_table;
		CoordsIntRectDims dims;
		/* The `top_left` coords are the coordinates of the potential tile in the top left
		 * corner of the `tile_rectangular_table`.
		 * This is useful to allow adding/removing rows/columns of tiles on the left/top
		 * without shifting the coords of all the other tiles. */
		CoordsInt top_left;

	public:
		Board(CoordsIntRectDims dims);
		bool is_there_a_tile_at(CoordsInt coords) const;
		Tile const& tile_at(CoordsInt coords) const;
		Tile& tile_at(CoordsInt coords);

		/* TODO: Add iterator on the tiles. */
	};
}

#endif /* HEADER_WHEN_THE_CHESS_LBOARD_ */
