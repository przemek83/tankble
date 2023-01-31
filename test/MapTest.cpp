#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include "catch2/generators/catch_generators.hpp"

#include "Config.h"
#include "Map.h"
#include "Point.h"
#include "Tank.h"

// 0 - plain
// 1 - brick
// 2 - water
// 3 - plant
// 4 - ice
// 5 - steel
// 6 - HQ
// M - my/player tank
// E - enemy tank
// S - speed up
// L - tier up
// A - shield up
// T - life up

namespace
{
const unsigned int tileCount{5};

std::string getTestMap()
{
    return {
        "E01TA\n"
        "01SL1\n"
        "E6010\n"
        "0213M\n"
        "50401\n"};
}

Point tileToPoint(unsigned int tileX, unsigned int tileY)
{
    static const unsigned int tileSize{Config::getInstance().getTileSize()};
    return {tileX * tileSize, tileY * tileSize};
}
}  // namespace

TEST_CASE("Map loading", "[map]")
{
    Map map(tileCount);
    std::stringstream stream(getTestMap());

    SECTION("check number of tanks")
    {
        auto tanks{map.loadMap(stream)};
        REQUIRE(tanks.size() == 3);
    }

    SECTION("check tanks location")
    {
        auto tanks{map.loadMap(stream)};
        const unsigned int tileSize{Config::getInstance().getTileSize()};
        REQUIRE(tanks[0].getLocation() == Point{0, 0});
        REQUIRE(tanks[1].getLocation() == Point{0, 2 * tileSize});
        REQUIRE(tanks[2].getLocation() == Point{4 * tileSize, 3 * tileSize});
    }
}

TEST_CASE("Check driving and flying", "[map]")
{
    Map map(tileCount);
    std::stringstream stream(getTestMap());

    SECTION("check driving")
    {
        using TestData = std::pair<Point, bool>;
        auto [point, expectedCanDrive] =
            GENERATE(TestData{tileToPoint(0, 0), true},
                     TestData{tileToPoint(1, 0), true},
                     TestData{tileToPoint(2, 0), false},
                     TestData{tileToPoint(3, 0), true},
                     TestData{tileToPoint(4, 0), true},
                     TestData{tileToPoint(0, 1), true},
                     TestData{tileToPoint(1, 1), false},
                     TestData{tileToPoint(2, 1), true},
                     TestData{tileToPoint(3, 1), true},
                     TestData{tileToPoint(4, 1), false},
                     TestData{tileToPoint(0, 2), true},
                     TestData{tileToPoint(1, 2), false},
                     TestData{tileToPoint(2, 2), true},
                     TestData{tileToPoint(3, 2), false},
                     TestData{tileToPoint(4, 2), true},
                     TestData{tileToPoint(0, 3), true},
                     TestData{tileToPoint(1, 3), false},
                     TestData{tileToPoint(2, 3), false},
                     TestData{tileToPoint(3, 3), true},
                     TestData{tileToPoint(4, 3), true},
                     TestData{tileToPoint(0, 4), false},
                     TestData{tileToPoint(1, 4), true},
                     TestData{tileToPoint(2, 4), true},
                     TestData{tileToPoint(3, 4), true},
                     TestData{tileToPoint(4, 4), false});

        map.loadMap(stream);
        REQUIRE(map.canDrive(point) == expectedCanDrive);
    }

    SECTION("check flying")
    {
        using TestData = std::pair<Point, bool>;
        auto [point, expectedCanFly] =
            GENERATE(TestData{tileToPoint(0, 0), true},
                     TestData{tileToPoint(1, 0), true},
                     TestData{tileToPoint(2, 0), false},
                     TestData{tileToPoint(3, 0), true},
                     TestData{tileToPoint(4, 0), true},
                     TestData{tileToPoint(0, 1), true},
                     TestData{tileToPoint(1, 1), false},
                     TestData{tileToPoint(2, 1), true},
                     TestData{tileToPoint(3, 1), true},
                     TestData{tileToPoint(4, 1), false},
                     TestData{tileToPoint(0, 2), true},
                     TestData{tileToPoint(1, 2), false},
                     TestData{tileToPoint(2, 2), true},
                     TestData{tileToPoint(3, 2), false},
                     TestData{tileToPoint(4, 2), true},
                     TestData{tileToPoint(0, 3), true},
                     TestData{tileToPoint(1, 3), true},
                     TestData{tileToPoint(2, 3), false},
                     TestData{tileToPoint(3, 3), true},
                     TestData{tileToPoint(4, 3), true},
                     TestData{tileToPoint(0, 4), false},
                     TestData{tileToPoint(1, 4), true},
                     TestData{tileToPoint(2, 4), true},
                     TestData{tileToPoint(3, 4), true},
                     TestData{tileToPoint(4, 4), false});

        map.loadMap(stream);
        REQUIRE(map.canFly(point) == expectedCanFly);
    }
}

TEST_CASE("Check hitting", "[map]")
{
    Map map(tileCount);
    std::stringstream stream(getTestMap());

    SECTION("check tile hit reaction")
    {
        using TestData = std::pair<Point, bool>;
        auto [point, expectedCanDriveAndFly] =
            GENERATE(TestData{tileToPoint(2, 0), true},
                     TestData{tileToPoint(1, 1), true},
                     TestData{tileToPoint(4, 1), true},
                     TestData{tileToPoint(1, 2), true},
                     TestData{tileToPoint(3, 2), true},
                     TestData{tileToPoint(2, 3), true},
                     TestData{tileToPoint(0, 4), false},
                     TestData{tileToPoint(4, 4), true});

        map.loadMap(stream);
        map.hit(point, 10);
        REQUIRE(map.canDrive(point) == expectedCanDriveAndFly);
        REQUIRE(map.canFly(point) == expectedCanDriveAndFly);
    }
}
