#include <algorithm>
#include <cstddef>
#include <sstream>

#include <catch2/catch_test_macros.hpp>

#include <src/Config.h>
#include <src/Game.h>
#include <src/Map.h>
#include <src/TankType.h>

#include "Common.h"
#include "FakeDisplay.h"
#include "src/InputAction.h"

namespace
{
Tank& getPlayerTank(std::list<Tank>& tanks)
{
    auto playerTankIt{std::find_if(tanks.begin(), tanks.end(),
                                   [](const Tank& tank)
                                   { return tank.isPlayerControlled(); })};

    return *playerTankIt;
}

void moveBulletsByOneTile(Game& game)
{
    for (int i{0}; i < 6; ++i)
        game.moveBullets();
}
};  // namespace

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
        Tank& playerTank{getPlayerTank(tanks)};

        // Decrease lives to one.
        playerTank.hit(playerTank.getStats().shield_);

        // Place enemy tank above player tank.
        point = common::tileToPoint(2, 2);
        tanks.emplace_back(TankType::ENEMY_TIER_4, point);
        Game game(tanks, map);

        // Let enemy tank fire.
        game.moveEnemyTanks();

        moveBulletsByOneTile(game);

        REQUIRE(game.isGameEnding(display));
    }
}

TEST_CASE("Player actions", "[Game]")
{
    Map map(common::tileCount);
    std::stringstream stream(common::getTestMap());
    std::list<Tank> tanks{map.loadMap(stream)};

    Point initialPosition{75, 105};
    SECTION("Check keeping position when not moved")
    {
        const Tank& playerTank{getPlayerTank(tanks)};
        Game game(tanks, map);
        Point center{playerTank.getCenter()};
        REQUIRE(center == initialPosition);
        game.movePlayerTank({});
        center = playerTank.getCenter();
        REQUIRE(center == initialPosition);
    }

    SECTION("Moving up through plain")
    {
        const Tank& playerTank{getPlayerTank(tanks)};
        Game game(tanks, map);
        game.movePlayerTank({InputAction::UP});
        Point center{playerTank.getCenter()};
        REQUIRE(center == Point{initialPosition.x_, initialPosition.y_ - 1});
    }

    SECTION("Moving down through plain")
    {
        const Tank& playerTank{getPlayerTank(tanks)};
        Game game(tanks, map);
        game.movePlayerTank({InputAction::DOWN});
        Point center{playerTank.getCenter()};
        REQUIRE(center == Point{initialPosition.x_, initialPosition.y_ + 1});
    }

    SECTION("Moving right through plant")
    {
        const Tank& playerTank{getPlayerTank(tanks)};
        Game game(tanks, map);
        game.movePlayerTank({InputAction::RIGHT});
        Point center{playerTank.getCenter()};
        REQUIRE(center == Point{initialPosition.x_ + 1, initialPosition.y_});
    }

    SECTION("Trying to move left through water")
    {
        const Tank& playerTank{getPlayerTank(tanks)};
        Game game(tanks, map);
        game.movePlayerTank({InputAction::LEFT});
        Point center{playerTank.getCenter()};
        REQUIRE(center == initialPosition);
    }

    SECTION("Firing towards enemy")
    {
        const std::size_t initialTanksCount{tanks.size()};
        Tank& playerTank{getPlayerTank(tanks)};
        playerTank.setLocation(common::tileToPoint(0, 1));
        Game game(tanks, map);
        game.movePlayerTank({InputAction::FIRE});
        moveBulletsByOneTile(game);
        REQUIRE(tanks.size() == initialTanksCount - 1);
    }
}

TEST_CASE("Drawing", "[Game]")
{
    Map map(common::tileCount);
    std::stringstream stream(common::getTestMap());
    std::list<Tank> tanks{map.loadMap(stream)};

    FakeDisplay display;

    SECTION("Check keeping position when not moved")
    {
        Game game(tanks, map);
        game.draw(display);
        // background 5x5 + foreground (plant) x1 + tank x3
        const std::size_t expectedCount{
            (common::tileCount * common::tileCount) + 1 + tanks.size()};
        REQUIRE(display.getChangedAreas().size() == expectedCount);
    }
}
