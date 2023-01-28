#include <catch2/catch_test_macros.hpp>

#include "Bullet.h"
#include "Config.h"
#include "Direction.h"
#include "TankType.h"

const unsigned int bulletPower{4};
const unsigned int bulletSpeed{10};
const Point point{10, 10};

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
}
