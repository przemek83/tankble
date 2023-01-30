#include <sstream>

#include <catch2/catch_test_macros.hpp>

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

TEST_CASE("Map loading", "[map]")
{
    const unsigned int tileCount{5};
    Map map(tileCount);
    const std::string testMap{
        "E01TA\n"
        "01SL1\n"
        "E6010\n"
        "0213M\n"
        "50401\n"};
    std::stringstream stream(testMap);

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
