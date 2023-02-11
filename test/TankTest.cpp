#include <catch2/catch_test_macros.hpp>
#include "catch2/generators/catch_generators.hpp"

#include "Config.h"
#include "Tank.h"

TEST_CASE("Tank creation", "[tank]")
{
    const Point point{10, 10};
    SECTION("check type - enemy")
    {
        const Tank tank(TankType::ENEMY_TIER_1, point);
        REQUIRE(tank.getTankType() == TankType::ENEMY_TIER_1);
    }

    SECTION("check type - player")
    {
        const Tank tank(TankType::PLAYER_TIER_1, point);
        REQUIRE(tank.getTankType() == TankType::PLAYER_TIER_1);
    }

    SECTION("check tank location")
    {
        const Tank tank(TankType::ENEMY_TIER_1, point);
        REQUIRE(tank.getLocation() == point);
    }

    SECTION("check tank center")
    {
        const Tank tank(TankType::ENEMY_TIER_1, point);
        REQUIRE(tank.getCenter() == Point{25, 25});
    }
}

TEST_CASE("Tank direction", "[tank]")
{
    const Point point{10, 10};
    SECTION("check direction - enemy")
    {
        const Tank tank(TankType::ENEMY_TIER_1, point);
        REQUIRE(tank.getDirection() == Direction::DOWN);
    }

    SECTION("check direction - player")
    {
        const Tank tank(TankType::PLAYER_TIER_1, point);
        REQUIRE(tank.getDirection() == Direction::UP);
    }

    SECTION("set direction")
    {
        Tank tank(TankType::PLAYER_TIER_1, point);
        const Direction newDirection{Direction::LEFT};
        tank.setDirection(newDirection);
        REQUIRE(tank.getDirection() == newDirection);
    }
}

TEST_CASE("check control", "[tank]")
{
    using TestData = std::pair<TankType, bool>;
    const auto [tankType, playerControlled] =
        GENERATE(TestData{TankType::ENEMY_TIER_1, false},
                 TestData{TankType::ENEMY_TIER_2, false},
                 TestData{TankType::ENEMY_TIER_3, false},
                 TestData{TankType::ENEMY_TIER_4, false},
                 TestData{TankType::PLAYER_TIER_1, true},
                 TestData{TankType::PLAYER_TIER_2, true},
                 TestData{TankType::PLAYER_TIER_3, true},
                 TestData{TankType::PLAYER_TIER_4, true});

    const Point point{10, 10};
    SECTION("check control")
    {
        const Tank tank(tankType, point);
        REQUIRE(tank.isPlayerControlled() == playerControlled);
    }
}

TEST_CASE("location related", "[tank]")
{
    const Point point{100, 100};
    SECTION("get location")
    {
        const Tank tank(TankType::ENEMY_TIER_1, point);
        REQUIRE(tank.getLocation() == Point{100, 100});
    }

    SECTION("get center")
    {
        const unsigned int halfOfTile{Config::getInstance().getTileSize() / 2};
        const Tank tank(TankType::ENEMY_TIER_1, point);
        REQUIRE(tank.getCenter() == Point{
                                        100 + halfOfTile,
                                        100 + halfOfTile,
                                    });
    }

    SECTION("is within")
    {
        const unsigned int tileSize{Config::getInstance().getTileSize()};
        using TestData = std::pair<Point, bool>;
        const auto [pointToTest, expectedIsWithin] = GENERATE_REF(
            TestData{Point{99, 99}, false}, TestData{Point{99, 100}, false},
            TestData{Point{100, 99}, false}, TestData{Point{100, 100}, true},
            TestData{Point{100 + tileSize - 1, 100}, true},
            TestData{Point{100 + tileSize, 100}, false},
            TestData{Point{100, 100 + tileSize - 1}, true},
            TestData{Point{100, 100 + tileSize}, false},
            TestData{Point{100 + tileSize - 1, 100 + tileSize - 1}, true},
            TestData{Point{100 + tileSize - 1, 100 + tileSize}, false},
            TestData{Point{100 + tileSize, 100 + tileSize - 1}, false},
            TestData{Point{100 + tileSize, 100 + tileSize}, false});

        const Tank tank(TankType::ENEMY_TIER_1, point);
        REQUIRE(tank.isWithin(pointToTest) == expectedIsWithin);
    }
}
