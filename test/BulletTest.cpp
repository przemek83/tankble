#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <src/Bullet.h>
#include <src/Config.h>
#include <src/Direction.h>
#include <src/Utils.h>

namespace
{
const int bulletPower{4};
const int bulletSpeed{10};
const Point point{5, 5};
const bool enemyOrigin{false};
const bool playerOrigin{true};

Bullet getExampleBullet()
{
    return {point, bulletSpeed, enemyOrigin, bulletPower, Direction::UP};
}
};  // namespace

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
        REQUIRE(currentPoint.x_ ==
                point.x_ -
                    utils::getMidpoint(Config::getInstance().getBulletSize()));
        REQUIRE(currentPoint.y_ ==
                point.y_ -
                    utils::getMidpoint(Config::getInstance().getBulletSize()));
    }
    SECTION("center is correct")
    {
        const Point currentPoint{bullet.getCenter()};
        REQUIRE(currentPoint.x_ == point.x_);
        REQUIRE(currentPoint.y_ == point.y_);
    }
    SECTION("getX is working")
    {
        const Point currentPoint{bullet.getLocation()};
        const int currentX{bullet.getX()};
        REQUIRE(currentX == currentPoint.x_);
    }
    SECTION("getY is working")
    {
        const Point currentPoint{bullet.getLocation()};
        const int currentY{bullet.getY()};
        REQUIRE(currentY == currentPoint.y_);
    }

    SECTION("setX is working")
    {
        const int newX{15};
        bullet.setX(newX);
        const int currentX{bullet.getX()};
        REQUIRE(currentX == newX);
    }

    SECTION("setY is working")
    {
        const int newY{27};
        bullet.setY(newY);
        const int currentY{bullet.getY()};
        REQUIRE(currentY == newY);
    }
}

TEST_CASE("Bullet moving", "[bullet]")
{
    SECTION("bullet moving with 0 speed")
    {
        Direction direction{GENERATE_REF(Direction::UP, Direction::DOWN,
                                         Direction::RIGHT, Direction::LEFT)};

        Bullet bullet{point, 0, enemyOrigin, bulletPower, direction};
        const Point centerBeforeMove{bullet.getCenter()};

        bullet.move();

        const Point centerAfterMove{bullet.getCenter()};
        REQUIRE(centerBeforeMove.x_ == centerAfterMove.x_);
        REQUIRE(centerBeforeMove.y_ == centerAfterMove.y_);
    }
    SECTION("bullet moving inside valid area")
    {
        using TestData = std::pair<Direction, Point>;
        const int middle{
            utils::getMidpoint(Config::getInstance().getBoardWidth())};
        auto [direction, expectedPoint] = GENERATE_REF(
            TestData{Direction::UP, Point{middle, middle - bulletSpeed}},
            TestData{Direction::DOWN, Point{middle, middle + bulletSpeed}},
            TestData{Direction::RIGHT, Point{middle + bulletSpeed, middle}},
            TestData{Direction::LEFT, Point{middle - bulletSpeed, middle}});

        const Point startPoint{middle, middle};
        Bullet bullet{startPoint, bulletSpeed, enemyOrigin, bulletPower,
                      direction};

        bullet.move();

        REQUIRE(bullet.getCenter().x_ == expectedPoint.x_);
        REQUIRE(bullet.getCenter().y_ == expectedPoint.y_);
    }
    SECTION("location and center not changed after invalid move")
    {
        Bullet bullet{getExampleBullet()};
        const Point centerBeforeMove{bullet.getCenter()};
        const Point locationBeforeMove{bullet.getLocation()};

        REQUIRE(bullet.move() == false);

        const Point centerAfterMove{bullet.getCenter()};
        REQUIRE(centerBeforeMove.x_ == centerAfterMove.x_);
        REQUIRE(centerBeforeMove.y_ == centerAfterMove.y_);
        const Point locationAfterMove{bullet.getLocation()};
        REQUIRE(locationBeforeMove.x_ == locationAfterMove.x_);
        REQUIRE(locationBeforeMove.y_ == locationAfterMove.y_);
    }
}

TEST_CASE("Bullet moving to invalid area", "[bullet]")
{
    using TestData = std::pair<Direction, Point>;
    const int nearEndOfMap{Config::getInstance().getBoardWidth() -
                           utils::getMidpoint(bulletSpeed)};
    auto [direction, pointGenerated] =
        GENERATE_REF(TestData{Direction::UP, point},
                     TestData{Direction::DOWN, Point{point.x_, nearEndOfMap}},
                     TestData{Direction::RIGHT, Point{nearEndOfMap, point.y_}},
                     TestData{Direction::LEFT, point});

    Bullet bullet{pointGenerated, bulletSpeed, enemyOrigin, bulletPower,
                  direction};

    REQUIRE(bullet.move() == false);
}
