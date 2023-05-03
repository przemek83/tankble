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

    SECTION("moving up")
    {
        const std::vector<Point> movePoints{
            MapUtils::getMovePoints(leftUpperCorner, Direction::UP)};
        REQUIRE(movePoints.front() == Point{110, 100});
        REQUIRE(movePoints.back() == Point{120, 100});
    }

    SECTION("moving down")
    {
        const std::vector<Point> movePoints{
            MapUtils::getMovePoints(leftUpperCorner, Direction::DOWN)};
        REQUIRE(movePoints.front() == Point{110, 129});
        REQUIRE(movePoints.back() == Point{120, 129});
    }

    SECTION("moving right")
    {
        const std::vector<Point> movePoints{
            MapUtils::getMovePoints(leftUpperCorner, Direction::RIGHT)};
        REQUIRE(movePoints.front() == Point{129, 110});
        REQUIRE(movePoints.back() == Point{129, 120});
    }

    SECTION("moving left")
    {
        const std::vector<Point> movePoints{
            MapUtils::getMovePoints(leftUpperCorner, Direction::LEFT)};
        REQUIRE(movePoints.front() == Point{100, 110});
        REQUIRE(movePoints.back() == Point{100, 120});
    }
}
