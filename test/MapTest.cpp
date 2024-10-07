#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include "catch2/generators/catch_generators.hpp"

#include <src/Config.h>
#include <src/Map.h>
#include <src/Point.h>
#include <src/Tank.h>
#include <src/Utils.h>

#include "Common.h"
#include "FakeDisplay.h"

// 0 - plain
// 1 - brick
// 2 - water
// 3 - plant
// 4 - ice
// 5 - steel
// 6 - HQ
// M - my/player tank
// E - enemy tank
// S - speed up
// L - tier up
// A - shield up
// T - life up

TEST_CASE("Map loading", "[map]")
{
    Map map(common::tileCount);
    std::stringstream stream(common::getTestMap());

    SECTION("check number of tanks")
    {
        auto tanks{map.loadMap(stream)};
        REQUIRE(tanks.size() == 3);
    }

    SECTION("check tanks location")
    {
        const auto tanks{map.loadMap(stream)};
        const int tileSize{Config::getInstance().getTileSize()};
        auto tankIter{tanks.begin()};
        REQUIRE(tankIter->getLocation() == Point{0, 0});
        REQUIRE((++tankIter)->getLocation() == Point{0, 2 * tileSize});
        REQUIRE((++tankIter)->getLocation() ==
                Point{4 * tileSize, 3 * tileSize});
    }
}

TEST_CASE("Check driving and flying", "[map]")
{
    Map map(common::tileCount);
    std::stringstream stream(common::getTestMap());

    SECTION("check driving")
    {
        using TestData = std::pair<Point, bool>;
        const auto [point, expectedCanDrive] =
            GENERATE(TestData{common::tileToPoint(0, 0), true},    // enemy
                     TestData{common::tileToPoint(1, 0), true},    // plain
                     TestData{common::tileToPoint(2, 0), false},   // brick
                     TestData{common::tileToPoint(3, 0), true},    // life
                     TestData{common::tileToPoint(4, 0), true},    // shiel
                     TestData{common::tileToPoint(0, 1), true},    // plain
                     TestData{common::tileToPoint(1, 1), false},   // brick
                     TestData{common::tileToPoint(2, 1), true},    // speed
                     TestData{common::tileToPoint(3, 1), true},    // tier
                     TestData{common::tileToPoint(4, 1), false},   // brick
                     TestData{common::tileToPoint(0, 2), true},    // enemy
                     TestData{common::tileToPoint(1, 2), false},   // base
                     TestData{common::tileToPoint(2, 2), true},    // plain
                     TestData{common::tileToPoint(3, 2), false},   // brick
                     TestData{common::tileToPoint(4, 2), true},    // plain
                     TestData{common::tileToPoint(0, 3), true},    // plain
                     TestData{common::tileToPoint(1, 3), false},   // water
                     TestData{common::tileToPoint(2, 3), false},   // brick
                     TestData{common::tileToPoint(3, 3), true},    // plant
                     TestData{common::tileToPoint(4, 3), true},    // playe
                     TestData{common::tileToPoint(0, 4), false},   // steel
                     TestData{common::tileToPoint(1, 4), true},    // plain
                     TestData{common::tileToPoint(2, 4), true},    // ice
                     TestData{common::tileToPoint(3, 4), true},    // plain
                     TestData{common::tileToPoint(4, 4), false});  // brick

        map.loadMap(stream);
        REQUIRE(map.canDrive(point) == expectedCanDrive);
    }

    SECTION("check flying")
    {
        using TestData = std::pair<Point, bool>;
        const auto [point, expectedCanFly] =
            GENERATE(TestData{common::tileToPoint(0, 0), true},    // enemy
                     TestData{common::tileToPoint(1, 0), true},    // plain
                     TestData{common::tileToPoint(2, 0), false},   // brick
                     TestData{common::tileToPoint(3, 0), true},    // life up
                     TestData{common::tileToPoint(4, 0), true},    // shield up
                     TestData{common::tileToPoint(0, 1), true},    // plain
                     TestData{common::tileToPoint(1, 1), false},   // brick
                     TestData{common::tileToPoint(2, 1), true},    // speed up
                     TestData{common::tileToPoint(3, 1), true},    // tier up
                     TestData{common::tileToPoint(4, 1), false},   // brick
                     TestData{common::tileToPoint(0, 2), true},    // enemy
                     TestData{common::tileToPoint(1, 2), false},   // base
                     TestData{common::tileToPoint(2, 2), true},    // plain
                     TestData{common::tileToPoint(3, 2), false},   // brick
                     TestData{common::tileToPoint(4, 2), true},    // plain
                     TestData{common::tileToPoint(0, 3), true},    // plain
                     TestData{common::tileToPoint(1, 3), true},    // water
                     TestData{common::tileToPoint(2, 3), false},   // brick
                     TestData{common::tileToPoint(3, 3), true},    // plant
                     TestData{common::tileToPoint(4, 3), true},    // player
                     TestData{common::tileToPoint(0, 4), false},   // steel
                     TestData{common::tileToPoint(1, 4), true},    // plain
                     TestData{common::tileToPoint(2, 4), true},    // ice
                     TestData{common::tileToPoint(3, 4), true},    // plain
                     TestData{common::tileToPoint(4, 4), false});  // brick
        map.loadMap(stream);
        REQUIRE(map.canFly(point) == expectedCanFly);
    }
}

TEST_CASE("Check hitting", "[map]")
{
    Map map(common::tileCount);
    std::stringstream stream(common::getTestMap());

    SECTION("check tiles reaction for hit")
    {
        using TestData = std::pair<Point, bool>;
        const auto [point, expectedCanDriveAndFly] =
            GENERATE(TestData{common::tileToPoint(4, 1), true},    // brick
                     TestData{common::tileToPoint(1, 2), true},    // base
                     TestData{common::tileToPoint(0, 4), false});  // steel

        map.loadMap(stream);
        map.hit(point, common::testHitStrength);
        REQUIRE(map.canDrive(point) == expectedCanDriveAndFly);
        REQUIRE(map.canFly(point) == expectedCanDriveAndFly);
    }

    SECTION("check water reaction for hit")
    {
        const Point point{common::tileToPoint(1, 3)};
        map.loadMap(stream);
        map.hit(point, common::testHitStrength);
        REQUIRE(map.canDrive(point) == false);
        REQUIRE(map.canFly(point) == true);
    }

    SECTION("check base status after hit")
    {
        const Point point{common::tileToPoint(1, 2)};
        map.loadMap(stream);
        REQUIRE(map.isBaseDestroyed() == false);
        map.hit(point, common::testHitStrength);
        REQUIRE(map.isBaseDestroyed() == true);
    }

    SECTION("hitting tile multiple times")
    {
        const Point point{common::tileToPoint(1, 2)};
        map.loadMap(stream);
        REQUIRE(map.isBaseDestroyed() == false);
        map.hit(point, utils::getMidpoint(common::testHitStrength));
        REQUIRE(map.isBaseDestroyed() == true);
    }
}

TEST_CASE("Power ups", "[map]")
{
    Map map(common::tileCount);
    std::stringstream stream(common::getTestMap());

    SECTION("taking power up")
    {
        using TestData = std::pair<Point, bool>;
        const auto [point, expectedPowerup] =
            GENERATE(TestData{common::tileToPoint(2, 0), false},   // brick
                     TestData{common::tileToPoint(3, 0), true},    // life up
                     TestData{common::tileToPoint(4, 0), true},    // shield up
                     TestData{common::tileToPoint(0, 1), false},   // plain
                     TestData{common::tileToPoint(2, 1), true},    // speed up
                     TestData{common::tileToPoint(3, 1), true},    // tier up
                     TestData{common::tileToPoint(1, 2), false},   // base
                     TestData{common::tileToPoint(3, 3), false},   // plant
                     TestData{common::tileToPoint(0, 4), false},   // ice
                     TestData{common::tileToPoint(2, 4), false});  // brick

        map.loadMap(stream);
        auto [currentPowerup, _]{map.takePowerUp(point)};
        REQUIRE(currentPowerup == expectedPowerup);
    }

    SECTION("retaking power up")
    {
        const Point point =
            GENERATE(Point{common::tileToPoint(3, 0)},   // life up
                     Point{common::tileToPoint(4, 0)},   // shield up
                     Point{common::tileToPoint(2, 1)},   // speed up
                     Point{common::tileToPoint(3, 1)});  // tier up

        map.loadMap(stream);
        auto [currentPowerup, _]{map.takePowerUp(point)};
        REQUIRE(currentPowerup == true);
        std::tie(currentPowerup, _) = map.takePowerUp(point);
        REQUIRE(currentPowerup == false);
    }

    SECTION("recognizing power ups")
    {
        using TestData = std::pair<Point, ResourceType>;
        auto [point, expectedResourceType] =
            GENERATE(TestData{common::tileToPoint(3, 0),
                              ResourceType::LIFE_UP},  // life up
                     TestData{common::tileToPoint(4, 0),
                              ResourceType::SHIELD_UP},  // shield up
                     TestData{common::tileToPoint(2, 1),
                              ResourceType::SPEED_UP},  // speed up
                     TestData{common::tileToPoint(3, 1),
                              ResourceType::TIER_UP});  // tier up

        map.loadMap(stream);
        auto [_, currentResourceType] = map.takePowerUp(point);
        REQUIRE(currentResourceType == expectedResourceType);
    }
}

namespace
{
std::string getTestMapForShifting()
{
    return {
        "000\n"
        "010\n"
        "000\n"};
}
}  // namespace

TEST_CASE("shift", "[map]")
{
    std::stringstream stream(getTestMapForShifting());
    static const int tileSize{Config::getInstance().getTileSize()};
    static const int twoTiles{tileSize * 2};

    const int tileCountForShifting{3};
    Map map(tileCountForShifting);
    map.loadMap(stream);

    SECTION("shift left while moving up")
    {
        using TestData = std::tuple<Point, Point, Direction>;
        auto [pointToShift, expectedShiftedPoint, direction] = GENERATE(
            TestData{{0, twoTiles - 1}, {0, twoTiles - 1}, Direction::UP},
            TestData{{1, twoTiles - 1}, {0, twoTiles - 1}, Direction::UP},
            TestData{{twoTiles - 1, twoTiles - 1},
                     {twoTiles, twoTiles - 1},
                     Direction::UP},
            TestData{{twoTiles, twoTiles - 1},
                     {twoTiles, twoTiles - 1},
                     Direction::UP},

            TestData{{0, 1}, {0, 1}, Direction::DOWN},
            TestData{{1, 1}, {0, 1}, Direction::DOWN},
            TestData{{twoTiles - 1, 1}, {twoTiles, 1}, Direction::DOWN},
            TestData{{twoTiles, 1}, {twoTiles, 1}, Direction::DOWN},

            TestData{{tileSize + 1, 0}, {tileSize + 1, 0}, Direction::RIGHT},
            TestData{{tileSize + 1, 1}, {tileSize + 1, 0}, Direction::RIGHT},
            TestData{{tileSize + 1, twoTiles - 1},
                     {tileSize + 1, twoTiles},
                     Direction::RIGHT},
            TestData{{tileSize + 1, twoTiles},
                     {tileSize + 1, twoTiles},
                     Direction::RIGHT},

            TestData{{twoTiles - 1, 0}, {twoTiles - 1, 0}, Direction::LEFT},
            TestData{{twoTiles - 1, 1}, {twoTiles - 1, 0}, Direction::LEFT},
            TestData{{twoTiles - 1, twoTiles - 1},
                     {twoTiles - 1, twoTiles},
                     Direction::LEFT},
            TestData{{twoTiles - 1, twoTiles},
                     {twoTiles - 1, twoTiles},
                     Direction::LEFT});
        map.shift(pointToShift, direction);
        REQUIRE(pointToShift == expectedShiftedPoint);
    }
}

TEST_CASE("changed area", "[map]")
{
    const int tileSize{Config::getInstance().getTileSize()};

    Map map(common::tileCount);
    std::stringstream stream(common::getTestMap());
    map.loadMap(stream);

    FakeDisplay display;
    map.drawBackground(display);
    map.drawForeground(display);

    SECTION("First draw on display")
    {
        REQUIRE(display.getChangedAreas().size() == (25 + 1));
    }

    display.resetChangedAreas();

    SECTION("change one tile and draw background")
    {
        map.tagAreaAsChanged({0, 0}, {0, 0});
        map.drawBackground(display);
        auto changed{display.getChangedAreas()};
        REQUIRE(display.getChangedAreas().size() == 1);
    }

    SECTION("change 2 tiles in line and draw background")
    {
        map.tagAreaAsChanged({0, 0}, {tileSize, 0});
        map.drawBackground(display);
        REQUIRE(display.getChangedAreas().size() == 2);
    }

    SECTION("change 2 tiles in column and draw background")
    {
        map.tagAreaAsChanged({0, 0}, {0, tileSize});
        map.drawBackground(display);
        REQUIRE(display.getChangedAreas().size() == 2);
    }

    SECTION("change 4 tiles and draw background")
    {
        map.tagAreaAsChanged({0, 0}, {tileSize, tileSize});
        map.drawBackground(display);
        REQUIRE(display.getChangedAreas().size() == 4);
    }

    SECTION("change one tile and draw foreground")
    {
        map.tagAreaAsChanged({3 * tileSize, 3 * tileSize},
                             {3 * tileSize, 3 * tileSize});
        map.drawForeground(display);
        REQUIRE(display.getChangedAreas().size() == 1);
    }

    SECTION("change 2 tiles in line and draw foreground")
    {
        map.tagAreaAsChanged({3 * tileSize, 3 * tileSize},
                             {4 * tileSize, 3 * tileSize});
        map.drawForeground(display);
        REQUIRE(display.getChangedAreas().size() == 1);
    }

    SECTION("change 2 tiles in column and draw foreground")
    {
        map.tagAreaAsChanged({3 * tileSize, 3 * tileSize},
                             {3 * tileSize, 4 * tileSize});
        map.drawForeground(display);
        REQUIRE(display.getChangedAreas().size() == 1);
    }

    SECTION("change 4 tiles and draw foreground")
    {
        map.tagAreaAsChanged({3 * tileSize, 3 * tileSize},
                             {4 * tileSize, 4 * tileSize});
        map.drawForeground(display);
        REQUIRE(display.getChangedAreas().size() == 1);
    }

    SECTION("tag invalid areas outside map")
    {
        map.tagAreaAsChanged({-1, -1}, {-1, -1});
        map.drawBackground(display);
        REQUIRE(display.getChangedAreas().size() == 0);
    }

    SECTION("tag invalid areas partly outside map")
    {
        map.tagAreaAsChanged({-1, -1}, {1, 1});
        map.drawBackground(display);
        REQUIRE(display.getChangedAreas().size() == 1);
    }
}
