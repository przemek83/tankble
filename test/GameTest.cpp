#include <algorithm>
#include <sstream>

#include <catch2/catch_test_macros.hpp>

#include <src/Config.h>
#include <src/Game.h>
#include <src/Map.h>
#include <src/TankType.h>

#include "Common.h"
#include "FakeDisplay.h"

TEST_CASE("Check winning conditions", "[Game]")
{
    FakeDisplay display;
    Config::getInstance().setDefaultSleepTimeInSeconds(0);

    Point point{0, 0};
    Map map(common::tileCount);
    std::stringstream stream(common::getTestMap());
    std::list<Tank> tanks{map.loadMap(stream)};

    SECTION("Check no more enemies")
    {
        tanks.clear();
        tanks.emplace_back(TankType::PLAYER_TIER_1, point);
        Game game(tanks, map);
        REQUIRE(game.isGameEnding(display));
    }

    SECTION("Check game continues")
    {
        Game game(tanks, map);
        REQUIRE(!game.isGameEnding(display));
    }

    SECTION("Check base destroyed")
    {
        Game game(tanks, map);
        map.hit(common::tileToPoint(1, 2), common::testHitStrength);
        REQUIRE(game.isGameEnding(display));
    }
}
