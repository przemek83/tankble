#include "PointUtils.h"

#include "Config.h"

namespace point_utils
{
bool isValidPoint(int x, int y, int objectSize)
{
    const int maxCoordinate{Config::getInstance().getBoardWidth() -
                            (objectSize - 1)};
    return (x < maxCoordinate) && (y < maxCoordinate) && (y >= 0) && (x >= 0);
}

bool isValidPoint(Point point)
{
    const int maxCoordinate{Config::getInstance().getBoardWidth()};
    return (point.x_ < maxCoordinate) && (point.x_ >= 0) &&
           (point.y_ < maxCoordinate) && (point.y_ >= 0);
}

};  // namespace point_utils
