#include <catch2/catch_test_macros.hpp>

#include <src/Status.h>

#include "FakeDisplay.h"

TEST_CASE("Status usage", "[Status]")
{
    FakeDisplay display;
    Status status{{100, 100}};
    SECTION("Check resource type")
    {
        REQUIRE(status.getResourceType() == ResourceType::BACKGROUND);
    }

    SECTION("Check center")
    {
        Point center{status.getCenter()};
        REQUIRE(center == Point{200, 300});
    }

    SECTION("Check texts when drawing empty stats")
    {
        status.draw(display);
        std::vector<FakeDisplay::DrawnText> drawnTexts{display.getDrawnTexts()};
        REQUIRE(drawnTexts.size() == 4);
        REQUIRE(drawnTexts[0].text_ == "Lives: 0");
        REQUIRE(drawnTexts[1].text_ == "Shield: 0");
        REQUIRE(drawnTexts[2].text_ == "Speed: 0");
        REQUIRE(drawnTexts[3].text_ == "Attack: 0");
    }

    SECTION("Check Positions when drawing empty stats")
    {
        status.draw(display);
        std::vector<FakeDisplay::DrawnText> drawnTexts{display.getDrawnTexts()};
        REQUIRE(drawnTexts[0].x_ == 200);
        REQUIRE(drawnTexts[0].y_ == 120);
        REQUIRE(drawnTexts[1].x_ == 200);
        REQUIRE(drawnTexts[1].y_ == 240);
        REQUIRE(drawnTexts[2].x_ == 200);
        REQUIRE(drawnTexts[2].y_ == 360);
        REQUIRE(drawnTexts[3].x_ == 200);
        REQUIRE(drawnTexts[3].y_ == 480);
    }
}
