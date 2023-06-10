#include "MapUtils.h"

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
}  // namespace MapUtils
