#include <catch2/catch_test_macros.hpp>

#include <src/Menu.h>

#include "FakeDisplay.h"

TEST_CASE("Menu usage", "[Menu]")
{
    FakeDisplay display;
    Menu menu(display);

    SECTION("isLevelPicked")
    {
        REQUIRE(menu.isLevelPicked(UserChoice::LEVEL_1));
        REQUIRE(menu.isLevelPicked(UserChoice::LEVEL_2));
        REQUIRE(menu.isLevelPicked(UserChoice::LEVEL_3));
        REQUIRE(menu.isLevelPicked(UserChoice::LEVEL_4));
        REQUIRE(menu.isLevelPicked(UserChoice::LEVEL_MENU) == false);
        REQUIRE(menu.isLevelPicked(UserChoice::EXIT) == false);
    }
}
