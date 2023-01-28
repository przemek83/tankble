#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "Bullet.h"
#include "Config.h"
#include "Direction.h"
#include "TankType.h"

const unsigned int bulletPower{4};
const unsigned int bulletSpeed{10};
const Point point{5, 5};

static Bullet getExampleBullet()
{
    return {point, bulletSpeed, TankType::ENEMY_TIER_1, bulletPower,
            Direction::UP};
}

TEST_CASE("Bullet getters", "[bullet]")
{
    const Bullet bullet{getExampleBullet()};

    SECTION("bullet power is set")
    {
        REQUIRE(bullet.getPower() == bulletPower);
    }
    SECTION("tank type is set")
    {
        REQUIRE(bullet.getTankType() == TankType::ENEMY_TIER_1);
    }
    SECTION("resource type is set")
    {
        REQUIRE(bullet.getResourceType() == ResourceType::BULLET);
    }
}

TEST_CASE("Bullet coordinates", "[bullet]")
{
    Bullet bullet{getExampleBullet()};

    SECTION("location is correct")
    {
        const Point currentPoint{bullet.getLocation()};
        REQUIRE(currentPoint.x == point.x - Config::BULLET_SIZE / 2);
        REQUIRE(currentPoint.y == point.y - Config::BULLET_SIZE / 2);
    }
    SECTION("center is correct")
    {
        const Point currentPoint{bullet.getCenter()};
        REQUIRE(currentPoint.x == point.x);
        REQUIRE(currentPoint.y == point.y);
    }
    SECTION("getX is working")
    {
        const Point currentPoint{bullet.getLocation()};
        const unsigned int currentX{bullet.getX()};
        REQUIRE(currentX == currentPoint.x);
    }
    SECTION("getY is working")
    {
        const Point currentPoint{bullet.getLocation()};
        const unsigned int currentY{bullet.getY()};
        REQUIRE(currentY == currentPoint.y);
    }

    SECTION("setX is working")
    {
        const unsigned int newX{15};
        bullet.setX(newX);
        const unsigned int currentX{bullet.getX()};
        REQUIRE(currentX == newX);
    }

    SECTION("setY is working")
    {
        const unsigned int newY{27};
        bullet.setY(newY);
        const unsigned int currentY{bullet.getY()};
        REQUIRE(currentY == newY);
    }
}

TEST_CASE("Bullet moving", "[bullet]")
{
    SECTION("bullet moving with 0 speed")
    {
        Bullet bullet{point, 0, TankType::ENEMY_TIER_1, bulletPower,
                      Direction::UP};
        const Point centerBeforeMove{bullet.getCenter()};
        bullet.move();
        const Point centerAfterMove{bullet.getCenter()};
        REQUIRE(centerBeforeMove.x == centerAfterMove.x);
        REQUIRE(centerBeforeMove.y == centerAfterMove.y);
    }
    SECTION("bullet moving down in valid area")
    {
        Bullet bullet{point, bulletSpeed, TankType::ENEMY_TIER_1, bulletPower,
                      Direction::DOWN};
        const Point centerBeforeMove{bullet.getCenter()};
        REQUIRE(bullet.move() == true);
        const Point centerAfterMove{bullet.getCenter()};
        REQUIRE(centerBeforeMove.x == centerAfterMove.x);
        REQUIRE(centerBeforeMove.y + bulletSpeed == centerAfterMove.y);
    }
    SECTION("bullet moving right in valid area")
    {
        Bullet bullet{point, bulletSpeed, TankType::ENEMY_TIER_1, bulletPower,
                      Direction::RIGHT};
        const Point centerBeforeMove{bullet.getCenter()};
        REQUIRE(bullet.move() == true);
        const Point centerAfterMove{bullet.getCenter()};
        REQUIRE(centerBeforeMove.x + bulletSpeed == centerAfterMove.x);
        REQUIRE(centerBeforeMove.y == centerAfterMove.y);
    }
    SECTION("location and center not changed after invalid move")
    {
        Bullet bullet{getExampleBullet()};
        const Point centerBeforeMove{bullet.getCenter()};
        const Point locationBeforeMove{bullet.getLocation()};
        REQUIRE(bullet.move() == false);
        const Point centerAfterMove{bullet.getCenter()};
        REQUIRE(centerBeforeMove.x == centerAfterMove.x);
        REQUIRE(centerBeforeMove.y == centerAfterMove.y);
        const Point locationAfterMove{bullet.getLocation()};
        REQUIRE(locationBeforeMove.x == locationAfterMove.x);
        REQUIRE(locationBeforeMove.y == locationAfterMove.y);
    }
}

TEST_CASE("Bullet moving to invalid area", "[bullet]")
{
    using inputPair = std::pair<Direction, Point>;
    const unsigned int nearEndOfMap{Config::mapSize * Config::elementSize -
                                    bulletSpeed / 2};
    auto [direction, pointGenerated] = GENERATE(table<Direction, Point>(
        {inputPair{Direction::UP, point},
         inputPair{Direction::DOWN, Point{point.x, nearEndOfMap}},
         inputPair{Direction::RIGHT, Point{nearEndOfMap, point.y}},
         inputPair{Direction::LEFT, point}}));

    Bullet bullet{pointGenerated, bulletSpeed, TankType::ENEMY_TIER_1,
                  bulletPower, direction};
    REQUIRE(bullet.move() == false);
}
