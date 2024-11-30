#include <catch2/catch_test_macros.hpp>

#include <src/MenuItem.h>
#include <src/Screen.h>

#include "FakeDisplay.h"

TEST_CASE("MenuItem initialization and properties", "[MenuItem]")
{
    MenuItem menuItem(UserChoice::LEVEL_MENU);

    SECTION("Creation")
    {
        REQUIRE(menuItem.getUserChoice() == UserChoice::LEVEL_MENU);
        REQUIRE(menuItem.getWidth() == 0);
        REQUIRE(menuItem.getHeight() == 0);
        REQUIRE(menuItem.getResourceType() == ResourceType::MENU_ITEM);
    }

    SECTION("Set selected")
    {
        menuItem.setSelected(true);
        REQUIRE(menuItem.getResourceType() == ResourceType::MENU_ITEM_SELECTED);
    }

    SECTION("Set not selected")
    {
        menuItem.setSelected(true);
        menuItem.setSelected(false);
        REQUIRE(menuItem.getResourceType() == ResourceType::MENU_ITEM);
    }

    SECTION("initialization")
    {
        const int itemsCount{3};
        const int resourceHeight{70};
        const int resourceWidth{340};

        FakeDisplay display;
        display.setResourceHeight(resourceHeight);
        display.setResourceWidth(resourceWidth);

        menuItem.init(display, 0, itemsCount);
        REQUIRE(menuItem.getX() == 230);
        REQUIRE(menuItem.getY() == 195);
        REQUIRE(menuItem.getWidth() == resourceWidth);
        REQUIRE(menuItem.getHeight() == resourceHeight);
        REQUIRE(menuItem.getCenter() == Point{170, 35});

        menuItem.init(display, 1, itemsCount);
        REQUIRE(menuItem.getX() == 230);
        REQUIRE(menuItem.getY() == 265);
        REQUIRE(menuItem.getWidth() == resourceWidth);
        REQUIRE(menuItem.getHeight() == resourceHeight);
        REQUIRE(menuItem.getCenter() == Point{170, 35});

        menuItem.init(display, 2, itemsCount);
        REQUIRE(menuItem.getX() == 230);
        REQUIRE(menuItem.getY() == 335);
        REQUIRE(menuItem.getWidth() == resourceWidth);
        REQUIRE(menuItem.getHeight() == resourceHeight);
        REQUIRE(menuItem.getCenter() == Point{170, 35});
    }

    SECTION("initialization of small item")
    {
        const int itemsCount{3};

        FakeDisplay display;
        display.setResourceHeight(display.getHeight() / 20);
        display.setResourceWidth(display.getWidth() / 20);

        menuItem.init(display, 0, itemsCount);
        REQUIRE(menuItem.getX() == 267);
        REQUIRE(menuItem.getY() == 210);
        REQUIRE(menuItem.getWidth() == 266);
        REQUIRE(menuItem.getHeight() == 60);
        REQUIRE(menuItem.getCenter() == Point{133, 30});
    }
}
