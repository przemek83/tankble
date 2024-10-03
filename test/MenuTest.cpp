#include <catch2/catch_test_macros.hpp>

#include <src/Level.h>
#include <src/Menu.h>

#include "FakeDisplay.h"
#include "src/InputAction.h"
#include "src/UserChoice.h"
#include "test/FakeInput.h"

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

    SECTION("getUserChoice EXIT")
    {
        FakeInput input{{InputAction::QUIT}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::EXIT);
    }

    SECTION("getUserChoice accept in main menu")
    {
        menu.refresh(UserChoice::MAIN_MENU);
        FakeInput input{{InputAction::ACCEPT}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::LEVEL_MENU);
    }

    SECTION("getUserChoice back in main menu")
    {
        menu.refresh(UserChoice::MAIN_MENU);
        FakeInput input{{InputAction::BACK}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::EXIT);
    }

    SECTION("getUserChoice back in level menu")
    {
        menu.refresh(UserChoice::LEVEL_MENU);
        FakeInput input{{InputAction::BACK}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::BACK);
    }

    SECTION("getUserChoice accept in level menu")
    {
        menu.refresh(UserChoice::LEVEL_MENU);
        FakeInput input{{InputAction::ACCEPT}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::LEVEL_1);
    }

    SECTION("getUserChoice down and accept in level menu")
    {
        menu.refresh(UserChoice::LEVEL_MENU);
        FakeInput input{{InputAction::DOWN, InputAction::ACCEPT}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::LEVEL_2);
    }

    SECTION("getUserChoice down and accept in level menu")
    {
        menu.refresh(UserChoice::LEVEL_MENU);
        FakeInput input{
            {InputAction::DOWN, InputAction::UP, InputAction::ACCEPT}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::LEVEL_1);
    }
}
