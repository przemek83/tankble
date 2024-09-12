#include "MapUtils.h"

namespace map_utils
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
                {leftUpperCorner.x_ + oneThirdOfTank, leftUpperCorner.y_},
                {leftUpperCorner.x_ + 2 * oneThirdOfTank, leftUpperCorner.y_}};
        }
        case Direction::DOWN:
        {
            return {{leftUpperCorner.x_ + oneThirdOfTank,
                     leftUpperCorner.y_ + tileSize - 1},
                    {leftUpperCorner.x_ + 2 * oneThirdOfTank,
                     leftUpperCorner.y_ + tileSize - 1}};
        }
        case Direction::LEFT:
        {
            return {
                {leftUpperCorner.x_, leftUpperCorner.y_ + oneThirdOfTank},
                {leftUpperCorner.x_, leftUpperCorner.y_ + 2 * oneThirdOfTank}};
        }
        case Direction::RIGHT:
        {
            return {{leftUpperCorner.x_ + tileSize - 1,
                     leftUpperCorner.y_ + oneThirdOfTank},
                    {leftUpperCorner.x_ + tileSize - 1,
                     leftUpperCorner.y_ + 2 * oneThirdOfTank}};
        }
    }

    return {};
}
}  // namespace map_utils
