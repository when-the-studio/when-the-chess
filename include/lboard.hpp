#ifndef HEADER_WHEN_THE_CHESS_LBOARD_
#define HEADER_WHEN_THE_CHESS_LBOARD_

#include <cstdint>
#include <optional>
#include <vector>

/* Designate the position of a tile in a 2D grid. */
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

	int surface() const;
};

/* Designate a rectangle of tiles in a 2D grid. */
class CoordsIntRect {
public:
	CoordsInt top_left;
	CoordsIntRectDims dims;

public:
	CoordsIntRect(CoordsInt top_left, CoordsIntRectDims dims);

	bool contains(CoordsInt coords) const;

	/* Returns the index of coords in this rect when we index all the tiles in the rect
	 * from 0 (top-left) to `this->dims.surface()-1` (bottom-right) in reading order
	 * (so that top-right has index `this->dims.w-1` for example). */
	int left_to_right_top_to_bottom_index(CoordsInt coords) const;
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
	public:
		Board(CoordsIntRect rect);

		bool is_there_a_tile_at(CoordsInt coords) const;

		Tile const& tile_at(CoordsInt coords) const;
		Tile& tile_at(CoordsInt coords);

	private:
		/* The tiles here are supposed to be squares arranged on a classic 2D grid.
		 * It has a rectangle (of dimentions specified by `rect.dims`) of potential tiles
		 * so that it has some freedom in its possible shapes (although the tiles
		 * should not be too far away from eachother as this would waste a lot of memory). */
		std::vector<std::optional<Tile>> table;
		/* The `rect.top_left` coords are the coordinates of the potential tile in the
		 * top-left corner of the `table`.
		 * This is useful to allow adding/removing rows/columns of tiles on the left/top
		 * without shifting the coords of all the other tiles. */
		CoordsIntRect rect;
	};
}

#endif /* HEADER_WHEN_THE_CHESS_LBOARD_ */
