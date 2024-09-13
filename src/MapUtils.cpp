#include "MapUtils.h"

namespace map_utils
{
std::vector<Point> getMovePoints(Point leftUpperCorner, Direction direction,
                                 int tileSize)
{
    const int tankThird{tileSize / 3};
    const int x{leftUpperCorner.x_};
    const int y{leftUpperCorner.y_};
    switch (direction)
    {
        case Direction::UP:
        {
            return {{x + tankThird, y}, {x + 2 * tankThird, y}};
        }
        case Direction::DOWN:
        {
            return {{x + tankThird, y + tileSize - 1},
                    {x + 2 * tankThird, y + tileSize - 1}};
        }
        case Direction::LEFT:
        {
            return {{x, y + tankThird}, {x, y + 2 * tankThird}};
        }
        case Direction::RIGHT:
        {
            return {{x + tileSize - 1, y + tankThird},
                    {x + tileSize - 1, y + 2 * tankThird}};
        }

        default:
            break;
    }

    return {};
}
}  // namespace map_utils
