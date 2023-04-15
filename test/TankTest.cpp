#include <chrono>

#include <catch2/catch_test_macros.hpp>
#include "catch2/generators/catch_generators.hpp"

#include "Bullet.h"
#include "Config.h"
#include "Tank.h"

TEST_CASE("Tank creation", "[tank]")
{
    const Point point{10, 10};
    SECTION("check type - enemy")
    {
        const Tank tank(TankType::ENEMY_TIER_1, point);
        REQUIRE(tank.isPlayerControlled() == false);
    }

    SECTION("check type - player")
    {
        const Tank tank(TankType::PLAYER_TIER_1, point);
        REQUIRE(tank.isPlayerControlled() == true);
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

    SECTION("moving")
    {
        const Point newPoint{200, 200};
        Tank tank(TankType::ENEMY_TIER_1, point);
        tank.move(newPoint);
        REQUIRE(tank.getLocation() == newPoint);
    }
}

TEST_CASE("statistics", "[tank]")
{
    const Point point{100, 100};
    SECTION("getting initial basic enemy statistics")
    {
        const Tank tank(TankType::ENEMY_TIER_1, point);
        REQUIRE(tank.getStats().attackPower == 1);
        REQUIRE(tank.getStats().health == 1);
        REQUIRE(tank.getStats().speed == 4);
        REQUIRE(tank.getStats().lives == 1);
    }

    SECTION("getting initial basic player statistics")
    {
        const Tank tank(TankType::PLAYER_TIER_1, point);
        REQUIRE(tank.getStats().attackPower == 1);
        REQUIRE(tank.getStats().health == 1);
        REQUIRE(tank.getStats().speed == 4);
        REQUIRE(tank.getStats().lives == 2);
    }
}

TEST_CASE("hitting", "[tank]")
{
    const Point point{100, 100};
    SECTION("single hit, not destroying")
    {
        Tank tank(TankType::ENEMY_TIER_2, point);
        CHECK(tank.getStats().health == 2);
        tank.hit(1);
        REQUIRE(tank.getStats().health == 1);
    }

    SECTION("double hit, not destroying")
    {
        Tank tank(TankType::ENEMY_TIER_3, point);
        CHECK(tank.getStats().health == 3);
        tank.hit(1);
        tank.hit(1);
        REQUIRE(tank.getStats().health == 1);
    }

    SECTION("single hit, destroying, no more lives")
    {
        Tank tank(TankType::ENEMY_TIER_1, point);
        tank.hit(1);
        REQUIRE(tank.getStats().health == 0);
    }

    SECTION("single hit, destroying, 1 more life")
    {
        Tank tank(TankType::PLAYER_TIER_1, point);
        CHECK(tank.getStats().lives == 2);
        tank.hit(1);
        REQUIRE(tank.getStats().lives == 1);
    }
}

TEST_CASE("respawn", "[tank]")
{
    const Point point{100, 100};
    SECTION("checking downgrading after respawn")
    {
        Tank tank(TankType::PLAYER_TIER_3, point);
        tank.hit(3);
        REQUIRE(tank.getStats().health == 1);
    }

    SECTION("check positions after respawn")
    {
        Tank tank(TankType::PLAYER_TIER_1, point);
        tank.move({200, 200});
        tank.hit(3);
        REQUIRE(tank.getLocation() == point);
    }

    SECTION("check direction after respawn")
    {
        Tank tank(TankType::PLAYER_TIER_1, point);
        tank.setDirection(Direction::LEFT);
        tank.hit(3);
        REQUIRE(tank.getDirection() == Direction::UP);
    }
}

TEST_CASE("firing", "[tank]")
{
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
    const std::chrono::seconds delay{Config::getInstance().getFireDelay()};

    const Point point{100, 100};
    SECTION("center of created bullet")
    {
        const unsigned int tileSize{Config::getInstance().getTileSize()};
        Tank tank(TankType::PLAYER_TIER_1, point);
        const Bullet bullet = tank.fire(TimePoint::max());
        const Point expectedBulletCenter{point.x + tileSize / 2,
                                         point.y + tileSize / 2};
        REQUIRE(bullet.getCenter() == expectedBulletCenter);
    }

    SECTION("first fire possibility")
    {
        const Tank tank(TankType::PLAYER_TIER_1, point);
        REQUIRE(tank.canFire(TimePoint() + delay) == true);
    }

    SECTION("second fire too soon")
    {
        Tank tank(TankType::PLAYER_TIER_1, point);
        const TimePoint firstFireTime{TimePoint() + delay};
        tank.fire(firstFireTime);
        REQUIRE(tank.canFire(firstFireTime + delay / 2) == false);
    }

    SECTION("second fire possible")
    {
        Tank tank(TankType::PLAYER_TIER_1, point);
        const TimePoint firstFireTime{TimePoint() + delay};
        tank.fire(firstFireTime);
        REQUIRE(tank.canFire(firstFireTime + delay) == true);
    }

    SECTION("reset fire")
    {
        Tank tank(TankType::PLAYER_TIER_1, point);
        const TimePoint firstFireTime{TimePoint() + delay};
        tank.fire(firstFireTime);
        tank.resetFire();
        REQUIRE(tank.canFire(firstFireTime + delay / 2) == true);
    }
}

namespace
{
void statsAreSame(TankStats left, TankStats right)
{
    REQUIRE(left.attackPower == right.attackPower);
    REQUIRE(left.health == right.health);
    REQUIRE(left.lives == right.lives);
    REQUIRE(left.speed == right.speed);
}
}  // namespace

TEST_CASE("power-ups", "[tank]")
{
    const Point point{100, 100};
    SECTION("shield-up full health")
    {
        Tank tank(TankType::PLAYER_TIER_1, point);
        const TankStats initialStats{tank.getStats()};
        tank.applyPowerUp(ResourceType::SHIELD_UP);
        statsAreSame(tank.getStats(), initialStats);
    }

    SECTION("shield-up partial health")
    {
        Tank tank(TankType::PLAYER_TIER_4, point);
        const TankStats initialStats{tank.getStats()};
        tank.hit(1);
        tank.applyPowerUp(ResourceType::SHIELD_UP);
        statsAreSame(tank.getStats(), initialStats);
    }

    SECTION("life-up")
    {
        Tank tank(TankType::PLAYER_TIER_4, point);
        const unsigned int initialLives{tank.getStats().lives};
        tank.applyPowerUp(ResourceType::LIFE_UP);
        REQUIRE(initialLives + 1 == tank.getStats().lives);
    }

    SECTION("tier-up basic tank")
    {
        Tank tank(TankType::PLAYER_TIER_1, point);
        tank.applyPowerUp(ResourceType::TIER_UP);
        REQUIRE(tank.getResourceType() == ResourceType::PLAYER_TANK_TIER_2);
    }

    SECTION("tier-up max tier tank")
    {
        Tank tank(TankType::PLAYER_TIER_4, point);
        tank.applyPowerUp(ResourceType::TIER_UP);
        REQUIRE(tank.getResourceType() == ResourceType::PLAYER_TANK_TIER_4);
    }
}
