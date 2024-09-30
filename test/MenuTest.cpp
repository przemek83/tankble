#include <catch2/catch_test_macros.hpp>

#include <src/Level.h>
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

    SECTION("isLevelPicked")
    {
        REQUIRE(menu.choiceToLevel(UserChoice::LEVEL_1) == Level::LEVEL_1);
        REQUIRE(menu.choiceToLevel(UserChoice::LEVEL_2) == Level::LEVEL_2);
        REQUIRE(menu.choiceToLevel(UserChoice::LEVEL_3) == Level::LEVEL_3);
        REQUIRE(menu.choiceToLevel(UserChoice::LEVEL_4) == Level::LEVEL_4);
        REQUIRE(menu.choiceToLevel(UserChoice::LEVEL_MENU) == Level::LEVEL_4);
        REQUIRE(menu.choiceToLevel(UserChoice::EXIT) == Level::LEVEL_4);
    }
}
