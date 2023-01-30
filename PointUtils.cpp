#include "PointUtils.h"

#include "Config.h"

namespace PointUtils
{
Point pointFromSigned(int x, int y)
{
    return {static_cast<unsigned int>(x), static_cast<unsigned int>(y)};
}

bool isValidPoint(int x, int y, unsigned int objectSize)
{
    const int maxCoordinate{
        static_cast<int>(Config::elementSize * Config::mapSize - objectSize)};
    return x < maxCoordinate && y < maxCoordinate && y >= 0 && x >= 0;
}

bool isValidPoint(Point point)
{
    const int maxCoordinate{
        static_cast<int>(Config::elementSize * Config::mapSize)};
    return point.x < maxCoordinate && point.y < maxCoordinate;
}

};  // namespace PointUtils
