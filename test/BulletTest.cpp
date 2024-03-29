#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <src/Bullet.h>
#include <src/Config.h>
#include <src/Direction.h>

const unsigned int bulletPower{4};
const unsigned int bulletSpeed{10};
const Point point{5, 5};
const bool enemyOrigin = false;
const bool playerOrigin = true;

static Bullet getExampleBullet()
{
    return {point, bulletSpeed, enemyOrigin, bulletPower, Direction::UP};
}

TEST_CASE("Bullet getters", "[bullet]")
{
    const Bullet bullet{getExampleBullet()};

    SECTION("bullet power is set")
    {
        REQUIRE(bullet.getPower() == bulletPower);
    }
    SECTION("origin is set to enemy")
    {
        REQUIRE(bullet.isPlayerOrigin() == enemyOrigin);
    }
    SECTION("origin is set to player")
    {
        const Bullet bulletToTest{point, bulletSpeed, playerOrigin, bulletPower,
                                  Direction::UP};
        REQUIRE(bulletToTest.isPlayerOrigin() == playerOrigin);
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
        REQUIRE(currentPoint.x ==
                point.x - Config::getInstance().getBulletSize() / 2);
        REQUIRE(currentPoint.y ==
                point.y - Config::getInstance().getBulletSize() / 2);
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
        Bullet bullet{point, 0, enemyOrigin, bulletPower, Direction::UP};
        const Point centerBeforeMove{bullet.getCenter()};

        bullet.move();

        const Point centerAfterMove{bullet.getCenter()};
        REQUIRE(centerBeforeMove.x == centerAfterMove.x);
        REQUIRE(centerBeforeMove.y == centerAfterMove.y);
    }
    SECTION("bullet moving inside valid area")
    {
        using TestData = std::pair<Direction, Point>;
        const unsigned int middle{Config::getInstance().getBoardWidth() / 2};
        auto [direction, expectedPoint] = GENERATE_REF(
            TestData{Direction::UP, Point{middle, middle - bulletSpeed}},
            TestData{Direction::DOWN, Point{middle, middle + bulletSpeed}},
            TestData{Direction::RIGHT, Point{middle + bulletSpeed, middle}},
            TestData{Direction::LEFT, Point{middle - bulletSpeed, middle}});

        const Point startPoint{middle, middle};
        Bullet bullet{startPoint, bulletSpeed, enemyOrigin, bulletPower,
                      direction};

        bullet.move();

        REQUIRE(bullet.getCenter().x == expectedPoint.x);
        REQUIRE(bullet.getCenter().y == expectedPoint.y);
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
    using TestData = std::pair<Direction, Point>;
    const unsigned int nearEndOfMap{Config::getInstance().getBoardWidth() -
                                    bulletSpeed / 2};
    auto [direction, pointGenerated] =
        GENERATE_REF(TestData{Direction::UP, point},
                     TestData{Direction::DOWN, Point{point.x, nearEndOfMap}},
                     TestData{Direction::RIGHT, Point{nearEndOfMap, point.y}},
                     TestData{Direction::LEFT, point});

    Bullet bullet{pointGenerated, bulletSpeed, enemyOrigin, bulletPower,
                  direction};

    REQUIRE(bullet.move() == false);
}
