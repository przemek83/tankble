#include <catch2/catch_test_macros.hpp>

#include "FakeDisplay.h"

TEST_CASE("Display initialization and properties", "[Display]")
{
    FakeDisplay display;

    SECTION("Initialization")
    {
        REQUIRE(display.getWidth() == 800);
        REQUIRE(display.getHeight() == 600);
    }

    SECTION("Get Center")
    {
        REQUIRE(display.getCenterX() == 400);
        REQUIRE(display.getCenterY() == 300);
    }

    SECTION("Set and Get Width")
    {
        display.setWidth(1200);
        REQUIRE(display.getWidth() == 1200);
    }

    SECTION("Set and Get Height")
    {
        display.setHeight(800);
        REQUIRE(display.getHeight() == 800);
    }
}