#pragma once

#include <vector>

#include "Direction.h"
#include "Point.h"

class Map;

namespace MapUtils
{
std::vector<Point> getMovingPoints(Point leftUpperCorner, Direction direction);
void shiftIfNeeded(Point& leftUpper, const Map& map, Direction direction);
}  // namespace MapUtils
