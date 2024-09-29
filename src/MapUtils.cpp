#include "MapUtils.h"

namespace map_utils
{
std::vector<Point> getMovePoints(Point leftUpperCorner, Direction direction,
                                 int tileSize)
{
    const int tankThird{tileSize / 3};
    const int x{leftUpperCorner.x_};
    const int y{leftUpperCorner.y_};
    const int tankTwoThird{2 * tankThird};
    switch (direction)
    {
        case Direction::UP:
        {
            return {{x + tankThird, y}, {x + tankTwoThird, y}};
        }
        case Direction::DOWN:
        {
            return {{x + tankThird, (y + tileSize) - 1},
                    {x + tankTwoThird, (y + tileSize) - 1}};
        }
        case Direction::LEFT:
        {
            return {{x, y + tankThird}, {x, y + tankTwoThird}};
        }
        case Direction::RIGHT:
        {
            return {{(x + tileSize) - 1, y + tankThird},
                    {(x + tileSize) - 1, y + tankTwoThird}};
        }

        default:
            break;
    }

    return {};
}
}  // namespace map_utils
