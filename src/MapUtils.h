#pragma once

#include <vector>

#include "Direction.h"
#include "Point.h"

class Map;

namespace MapUtils
{
std::vector<Point> getMovePoints(Point leftUpperCorner, Direction direction,
                                 unsigned int tileSize);
}  // namespace MapUtils
