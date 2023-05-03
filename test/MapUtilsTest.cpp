#include <catch2/catch_test_macros.hpp>

#include "MapUtils.h"

TEST_CASE("Move points", "[MapUtils]")
{
    const Point leftUpperCorner{100, 100};

    SECTION("number of point returned")
    {
        const std::vector<Point> movePoints{
            MapUtils::getMovePoints(leftUpperCorner, Direction::UP)};
        REQUIRE(movePoints.size() == 2);
    }
}
