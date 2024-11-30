#include <catch2/catch_test_macros.hpp>

#include <src/Config.h>
#include <src/Level.h>
#include <src/Menu.h>

#include "FakeDisplay.h"
#include "FakeInput.h"
#include "src/InputAction.h"
#include "src/ResourceType.h"
#include "src/UserChoice.h"

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

    SECTION("getUserChoice back in options menu")
    {
        menu.refresh(UserChoice::OPTIONS_MENU);
        FakeInput input{{InputAction::BACK}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::BACK);
    }

    SECTION("getUserChoice accept in options menu")
    {
        menu.refresh(UserChoice::OPTIONS_MENU);
        FakeInput input{{InputAction::ACCEPT}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::FULLSCREEN);
    }

    SECTION("getUserChoice fullscreen")
    {
        menu.refresh(UserChoice::FULLSCREEN);
        FakeInput input{{InputAction::ACCEPT}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::FULLSCREEN);
    }

    SECTION("getUserChoice windowed")
    {
        menu.refresh(UserChoice::WINDOWED);
        FakeInput input{{InputAction::ACCEPT}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::FULLSCREEN);
    }

    SECTION("getUserChoice down and accept in level menu")
    {
        menu.refresh(UserChoice::LEVEL_MENU);
        FakeInput input{{InputAction::DOWN, InputAction::ACCEPT}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::LEVEL_2);
    }

    SECTION("getUserChoice up being on first item in level menu")
    {
        menu.refresh(UserChoice::LEVEL_MENU);
        FakeInput input{{InputAction::UP, InputAction::ACCEPT}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::LEVEL_1);
    }

    SECTION("getUserChoice down, up and accept in level menu")
    {
        menu.refresh(UserChoice::LEVEL_MENU);
        FakeInput input{
            {InputAction::DOWN, InputAction::UP, InputAction::ACCEPT}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::LEVEL_1);
    }

    SECTION("getUserChoice unsuported key in level menu")
    {
        menu.refresh(UserChoice::LEVEL_MENU);
        FakeInput input{{InputAction::LEFT, InputAction::ACCEPT}, {}, {}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::LEVEL_1);
    }

    SECTION("getUserChoice use mouse to pick last item in level menu")
    {
        menu.refresh(UserChoice::LEVEL_MENU);
        FakeInput input{{InputAction::MOUSE_MOVE, InputAction::ACCEPT},
                        {},
                        {Config::getInstance().getBoardWidth() / 2, 400}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::BACK);
    }

    SECTION("getUserChoice down being on last item in level menu")
    {
        menu.refresh(UserChoice::LEVEL_MENU);
        FakeInput input{
            {InputAction::MOUSE_MOVE, InputAction::DOWN, InputAction::ACCEPT},
            {},
            {Config::getInstance().getBoardWidth() / 2, 400}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::BACK);
    }

    SECTION("getUserChoice click outside items in level menu")
    {
        menu.refresh(UserChoice::LEVEL_MENU);
        FakeInput input{{InputAction::DOWN, InputAction::MOUSE_MOVE,
                         InputAction::CLICK, InputAction::ACCEPT},
                        {},
                        {0, 0}};
        UserChoice choice{menu.getUserChoice(input)};
        REQUIRE(choice == UserChoice::LEVEL_2);
    }

    SECTION("getUserChoice timer event with redrawing in level menu")
    {
        menu.refresh(UserChoice::LEVEL_MENU);
        FakeInput input{{InputAction::TIMER, InputAction::ACCEPT}, {}, {}};
        display.resetChangedAreas();
        menu.getUserChoice(input);
        std::vector<FakeDisplay::ChangedArea> changed{
            display.getChangedAreas()};
        REQUIRE(changed.size() == 5);
        REQUIRE(changed[0].type_ == ResourceType::MENU_ITEM_SELECTED);
        REQUIRE(changed[4].type_ == ResourceType::MENU_ITEM);
    }

    SECTION("getUserChoice hovering on last item with redrawing in level menu")
    {
        menu.refresh(UserChoice::LEVEL_MENU);
        FakeInput input{
            {InputAction::MOUSE_MOVE, InputAction::TIMER, InputAction::ACCEPT},
            {},
            {Config::getInstance().getBoardWidth() / 2, 400}};
        display.resetChangedAreas();
        menu.getUserChoice(input);
        std::vector<FakeDisplay::ChangedArea> changed{
            display.getChangedAreas()};
        REQUIRE(changed.size() == 5);
        REQUIRE(changed[0].type_ == ResourceType::MENU_ITEM);
        REQUIRE(changed[4].type_ == ResourceType::MENU_ITEM_SELECTED);
    }
}
