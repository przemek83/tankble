#include "MapUtils.h"

#include "Config.h"
#include "Map.h"

namespace
{
void shiftRight(Point& point, unsigned int tileSize)
{
    point.x = (point.x / tileSize + 1) * tileSize;
}

void shiftLeft(Point& point, unsigned int tileSize)
{
    point.x = (point.x / tileSize) * tileSize;
}

void shiftUp(Point& point, unsigned int tileSize)
{
    point.y = (point.y / tileSize) * tileSize;
}

void shiftDown(Point& point, unsigned int tileSize)
{
    point.y = (point.y / tileSize + 1) * tileSize;
}
}  // namespace

namespace MapUtils
{
std::vector<Point> getMovePoints(Point leftUpperCorner, Direction direction,
                                 unsigned int tileSize)
{
    const unsigned int oneThirdOfTank{tileSize / 3};
    switch (direction)
    {
        case Direction::UP:
        {
            return {
                {leftUpperCorner.x + oneThirdOfTank, leftUpperCorner.y},
                {leftUpperCorner.x + 2 * oneThirdOfTank, leftUpperCorner.y}};
        }
        case Direction::DOWN:
        {
            return {{leftUpperCorner.x + oneThirdOfTank,
                     leftUpperCorner.y + tileSize - 1},
                    {leftUpperCorner.x + 2 * oneThirdOfTank,
                     leftUpperCorner.y + tileSize - 1}};
        }
        case Direction::LEFT:
        {
            return {
                {leftUpperCorner.x, leftUpperCorner.y + oneThirdOfTank},
                {leftUpperCorner.x, leftUpperCorner.y + 2 * oneThirdOfTank}};
        }
        case Direction::RIGHT:
        {
            return {{leftUpperCorner.x + tileSize - 1,
                     leftUpperCorner.y + oneThirdOfTank},
                    {leftUpperCorner.x + tileSize - 1,
                     leftUpperCorner.y + 2 * oneThirdOfTank}};
        }
    }

    return {};
}

void shiftIfNeeded(Point& leftUpper, const Map& map, Direction direction)
{
    const unsigned int tileSize{Config::getInstance().getTileSize()};
    const Point leftLower{leftUpper.x, leftUpper.y + tileSize - 1};
    const Point rightUpper{leftUpper.x + tileSize - 1, leftUpper.y};
    const Point rightLower{leftUpper.x + tileSize - 1,
                           leftUpper.y + tileSize - 1};
    switch (direction)
    {
        case Direction::UP:
        case Direction::DOWN:
        {
            if (!map.canDrive(leftUpper) || !map.canDrive(leftLower))
                shiftRight(leftUpper, tileSize);

            if (!map.canDrive(rightUpper) || !map.canDrive(rightLower))
                shiftLeft(leftUpper, tileSize);
            break;
        }

        case Direction::LEFT:
        case Direction::RIGHT:
        {
            if (!map.canDrive(leftUpper) || !map.canDrive(rightUpper))
                shiftDown(leftUpper, tileSize);

            if (!map.canDrive(leftLower) || !map.canDrive(rightLower))
                shiftUp(leftUpper, tileSize);
            break;
        }
    }
}
}  // namespace MapUtils
