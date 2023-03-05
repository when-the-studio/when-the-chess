#include <cassert>
#include "lboard.hpp"

CoordsInt::CoordsInt(int x, int y):
x{x}, y{y} {}

CoordsIntRectDims::CoordsIntRectDims(int w, int h):
w{w}, h{h} {
	assert(0 <= w && 0 <= h);
}
