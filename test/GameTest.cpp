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

    SECTION("Check player destroyed")
    {
        auto playerTankIt{std::find_if(tanks.begin(), tanks.end(),
                                       [](const Tank& tank)
                                       { return tank.isPlayerControlled(); })};

        // Decrease lives to one.
        playerTankIt->hit(playerTankIt->getStats().shield_);

        // Place enemy tank above player tank.
        point = common::tileToPoint(2, 2);
        tanks.emplace_back(TankType::ENEMY_TIER_4, point);
        Game game(tanks, map);

        // Let enenymy tank fire.
        game.moveEnemyTanks();

        // Let bullet destroy player tank.
        for (int i{0}; i < 5; ++i)
            game.moveBullets();

        REQUIRE(game.isGameEnding(display));
    }
}
