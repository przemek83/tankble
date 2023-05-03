#pragma once

#include <vector>

#include "Direction.h"
#include "Point.h"

class Map;

namespace MapUtils
{
std::vector<Point> getMovePoints(Point leftUpperCorner, Direction direction,
                                 unsigned int tileSize);
void shiftIfNeeded(Point& leftUpper, const Map& map, Direction direction);
}  // namespace MapUtils
