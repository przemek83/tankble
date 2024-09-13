#pragma once

#include <vector>

#include "Direction.h"
#include "Point.h"

class Map;

namespace map_utils
{
std::vector<Point> getMovePoints(Point leftUpperCorner, Direction direction,
                                 int tileSize);
}  // namespace map_utils
