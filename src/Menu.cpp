#include "Menu.h"

#include <vector>

#include "Display.h"
#include "Input.h"
#include "InputAction.h"
#include "Level.h"
#include "MenuItem.h"
#include "UserChoice.h"
#include "Utils.h"

Menu::Menu(Display& display) : display_(display) {}

void Menu::refresh(UserChoice choice)
{
    switch (choice)
    {
        case UserChoice::MAIN_MENU:
        case UserChoice::BACK:
            initMainMenu();
            break;

        case UserChoice::LEVEL_MENU:
            initNewGameMenu();
            break;

        case UserChoice::OPTIONS_MENU:
            initOptionsMenu();
            break;

        case UserChoice::WINDOWED:
            display_.useWindowedMode();
            initOptionsMenu();
            break;

        case UserChoice::FULLSCREEN:
            display_.useFullScreenMode();
            initOptionsMenu();
            break;

        default:
            break;
    }
}

bool Menu::isLevelPicked(UserChoice choice) const
{
    return (choice == UserChoice::LEVEL_1) || (choice == UserChoice::LEVEL_2) ||
           (choice == UserChoice::LEVEL_3) || (choice == UserChoice::LEVEL_4);
}

Level Menu::choiceToLevel(UserChoice choice) const
{
    switch (choice)
    {
        case UserChoice::LEVEL_1:
            return Level::LEVEL_1;

        case UserChoice::LEVEL_2:
            return Level::LEVEL_2;

        case UserChoice::LEVEL_3:
            return Level::LEVEL_3;

        case UserChoice::LEVEL_4:
            return Level::LEVEL_4;

        default:
            return Level::LEVEL_1;
    }
}

void Menu::drawMenuItems(int currentItem)
{
    const std::size_t count{items_.size()};
    for (std::size_t item{0}; item < count; ++item)
    {
        items_[item].setSelected(static_cast<int>(item) == currentItem);
        items_[item].draw(display_);
    }
}

int Menu::getCurrentItem(std::pair<int, int> mousePosition, InputAction action,
                         int currentItem) const
{
    if ((action == InputAction::UP) && (currentItem > 0))
        return currentItem - 1;

    if ((action == InputAction::DOWN) &&
        (currentItem < static_cast<int>(items_.size() - 1)))
        return currentItem + 1;

    if (action != InputAction::MOUSE_MOVE)
        return currentItem;

    const auto [found, item]{getPointedItem(mousePosition)};
    if (found)
        return item;

    return currentItem;
}

void Menu::redraw(int currentItem)
{
    display_.drawBackground(ResourceType::BACKGROUND);
    drawMenuItems(currentItem);
    display_.refresh();
}

void Menu::initMenu(std::vector<UserChoice> userChoices)
{
    items_.clear();
    const std::size_t count{userChoices.size()};
    for (std::size_t i{0}; i < count; ++i)
    {
        MenuItem item{userChoices.at(i)};
        item.init(display_, static_cast<int>(i), static_cast<int>(count));
        items_.emplace_back(std::move(item));
    }
}

void Menu::initMainMenu()
{
    initMenu(
        {UserChoice::LEVEL_MENU, UserChoice::OPTIONS_MENU, UserChoice::EXIT});
}

void Menu::initNewGameMenu()
{
    initMenu({UserChoice::LEVEL_1, UserChoice::LEVEL_2, UserChoice::LEVEL_3,
              UserChoice::LEVEL_4, UserChoice::BACK});
}

void Menu::initOptionsMenu()
{
    initMenu({UserChoice::FULLSCREEN, UserChoice::WINDOWED, UserChoice::BACK});
}

bool Menu::mouseIsHoveringItem(std::pair<int, int> mousePosition,
                               int item) const
{
    const int firstItemY{items_.front().getY()};
    const auto [mouseX, mouseY] = mousePosition;
    const int itemWidth{items_.front().getWidth()};
    const int itemHeight{items_.front().getHeight()};
    return (mouseX > (display_.getCenterX() - utils::getMidpoint(itemWidth))) &&
           (mouseX < (display_.getCenterX() + utils::getMidpoint(itemWidth))) &&
           (mouseY > (firstItemY + (itemHeight * item))) &&
           (mouseY < (firstItemY + itemHeight + (itemHeight * item)));
}

std::pair<bool, int> Menu::getPointedItem(
    std::pair<int, int> mousePosition) const
{
    const int count{static_cast<int>(items_.size())};
    for (int item{0}; item < count; ++item)
    {
        if (mouseIsHoveringItem(mousePosition, item))
            return {true, item};
    }
    return {false, 0};
}

UserChoice Menu::getUserChoice()
{
    Input input;
    int currentItem{0};
    while (true)
    {
        const InputAction action{input.getMenuAction()};

        if (action == InputAction::QUIT)
            return UserChoice::EXIT;

        if (action == InputAction::ACCEPT)
            return items_[static_cast<std::size_t>(currentItem)]
                .getUserChoice();

        if (action == InputAction::BACK)
            return items_.back().getUserChoice();

        currentItem =
            getCurrentItem(input.getMousePosition(), action, currentItem);

        if (action == InputAction::TIMER)
            redraw(currentItem);
    }
}
