#include <catch2/catch_test_macros.hpp>

#include <src/MenuItem.h>
#include <src/Screen.h>

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
}