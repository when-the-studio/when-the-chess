#include <cassert>
#include "lboard.hpp"

CoordsInt::CoordsInt(int x, int y):
x{x}, y{y} {}

CoordsIntRectDims::CoordsIntRectDims(int w, int h):
w{w}, h{h} {
	assert(0 <= w && 0 <= h);
}

int CoordsIntRectDims::surface() const {
	return this->w * this->h;
}

CoordsIntRect::CoordsIntRect(CoordsInt top_left, CoordsIntRectDims dims):
top_left{top_left}, dims{dims} {}

bool CoordsIntRect::contains(CoordsInt coords) const {
	return
		this->top_left.x <= coords.x && coords.x < this->top_left.x + this->dims.w &&
		this->top_left.y <= coords.y && coords.y < this->top_left.y + this->dims.h;
}

int CoordsIntRect::left_to_right_top_to_bottom_index(CoordsInt coords) const {
	assert(this->contains(coords));
	return (coords.y - this->top_left.y) * this->dims.w + (coords.x - this->top_left.x);
}

namespace logical {
	Board::Board(CoordsIntRect rect):
	table{rect.dims.surface(), std::nullopt},
	rect{rect} {}

	bool Board::is_there_a_tile_at(CoordsInt coords) const {
		return this->rect.contains(coords);
	}
	
	Tile const& Board::tile_at(CoordsInt coords) const {
		int const index = this->rect.left_to_right_top_to_bottom_index(coords);
		std::optional<Tile> const& opt_tile = this->table[index];
		assert(opt_tile.has_value());
		return opt_tile.value();
	}
	Tile& Board::tile_at(CoordsInt coords) {
		int const index = this->rect.left_to_right_top_to_bottom_index(coords);
		std::optional<Tile>& opt_tile = this->table[index];
		assert(opt_tile.has_value());
		return opt_tile.value();
	}

	CoordsIntRect const& Board::rect_that_contains_all_the_tiles() const {
		return this->rect;
	}
}
