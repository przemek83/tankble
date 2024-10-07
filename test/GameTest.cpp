#include <catch2/catch_test_macros.hpp>

#include <src/Game.h>
#include <src/Map.h>

#include "src/Config.h"
#include "src/TankType.h"
#include "test/FakeDisplay.h"

TEST_CASE("Check winning conditions", "[Game]")
{
    FakeDisplay display;
    Config::getInstance().setDefaultSleepTimeInSeconds(0);

    std::list<Tank> tanks;
    Point point{0, 0};
    Map map{3};

    SECTION("Check no more enemies")
    {
        tanks.emplace_back(TankType::PLAYER_TIER_1, point);
        Game game(tanks, map);
        REQUIRE(game.isGameEnding(display));
    }

    SECTION("Check game continues")
    {
        tanks.emplace_back(TankType::PLAYER_TIER_1, point);
        tanks.emplace_back(TankType::ENEMY_TIER_1, point);
        Game game(tanks, map);
        REQUIRE(!game.isGameEnding(display));
    }
}
