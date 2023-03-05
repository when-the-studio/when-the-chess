#include <cassert>
#include "lboard.hpp"

CoordsInt::CoordsInt(int x, int y):
x{x}, y{y} {}

bool CoordsInt::operator==(CoordsInt rhs) const {
	return this->x == rhs.x && this->y == rhs.y;
}

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

int CoordsIntRect::top() const {
	return this->top_left.y;
}
int CoordsIntRect::bottom() const {
	return this->top_left.y + this->dims.h;
}
int CoordsIntRect::left() const {
	return this->top_left.x;
}
int CoordsIntRect::right() const {
	return this->top_left.x + this->dims.w;
}

int CoordsIntRect::left_to_right_top_to_bottom_index(CoordsInt coords) const {
	assert(this->contains(coords));
	return (coords.y - this->top_left.y) * this->dims.w + (coords.x - this->top_left.x);
}

CoordsInt const& CoordsIntRect::Iterator::operator*() const {
	return this->current_coords;
}
CoordsIntRect::Iterator& CoordsIntRect::Iterator::operator++() {
	this->current_coords.x++;
	if (this->current_coords.x > this->rect.right()) {
		/* Next line. */
		this->current_coords.x = this->rect.left();
		this->current_coords.y++;
	}
	return *this;
}
CoordsIntRect::Iterator CoordsIntRect::Iterator::operator++(int) {
	Iterator copy = *this;
	++(*this);
	return copy;
}
bool CoordsIntRect::Iterator::operator==(Iterator const& rhs) const {
	return this->current_coords == rhs.current_coords;
}
bool CoordsIntRect::Iterator::operator!=(Iterator const& rhs) const {
	return not (*this == rhs);
}
	
CoordsIntRect::Iterator::Iterator(CoordsIntRect const& rect, CoordsInt starting_coords):
current_coords{starting_coords}, rect{rect} {}

CoordsIntRect::Iterator CoordsIntRect::begin() const {
	return Iterator{*this, this->top_left};
}
CoordsIntRect::Iterator CoordsIntRect::end() const {
	/* The last tile that will be iterated over by an iterator will be the
	 * last tile of the last line, and incrementing it one more time will
	 * make it go on the first tile of the line after the last one, which
	 * is thus exactly the tile that this past-the-end iterator must be on. */
	return Iterator{*this, CoordsInt{this->left(), this->bottom()+1}};
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
