#include "Menu.h"

#include <vector>

#include "Input.h"
#include "InputAction.h"
#include "Level.h"
#include "MenuItem.h"
#include "Screen.h"

Menu::Menu(Screen& screen) : screen_(screen) { initMainMenu(); }

std::pair<bool, Level> Menu::playGame()
{
    Screen::showMouse();

    for (;;)
    {
        switch (getUserChoice())
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
                screen_.useWindowedMode();
                initOptionsMenu();
                break;

            case UserChoice::FULLSCREEN:
                screen_.useFullScreenMode();
                initOptionsMenu();
                break;

            case UserChoice::EXIT:
                Screen::hideMouse();
                return {false, Level::LEVEL_1};

            case UserChoice::LEVEL_1:
                Screen::hideMouse();
                return {true, Level::LEVEL_1};

            case UserChoice::LEVEL_2:
                Screen::hideMouse();
                return {true, Level::LEVEL_2};

            case UserChoice::LEVEL_3:
                Screen::hideMouse();
                return {true, Level::LEVEL_3};

            case UserChoice::LEVEL_4:
                Screen::hideMouse();
                return {true, Level::LEVEL_4};

            default:
                break;
        }
    }
}

void Menu::drawMenuItems(int currentItem)
{
    for (std::size_t item{0}; item < items_.size(); ++item)
    {
        items_[item].setSelected(static_cast<int>(item) == currentItem);
        items_[item].draw(screen_);
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
    screen_.drawBackground(ResourceType::BACKGROUND);
    drawMenuItems(currentItem);
    Screen::refresh();
}

int Menu::getLocationOfFirstItem(int count) const
{
    return screen_.getCenterY() - (count * getItemHeight() / 2);
}

int Menu::getItemWidth() const
{
    return std::max(screen_.getWidth() / 3,
                    screen_.getResourceWidth(ResourceType::MENU_ITEM));
}

int Menu::getItemHeight() const
{
    return std::max(screen_.getHeight() / 10,
                    screen_.getResourceHeight(ResourceType::MENU_ITEM));
}

void Menu::initMenu(std::vector<UserChoice> userChoices)
{
    items_.clear();
    const std::size_t count{userChoices.size()};
    for (std::size_t i{0}; i < count; ++i)
    {
        MenuItem item{
            getItemPosition(static_cast<int>(i), static_cast<int>(count)),
            userChoices.at(i)};
        item.initDimensions(screen_);
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

Point Menu::getItemPosition(int item, int count) const
{
    const int itemWidth{getItemWidth()};
    const int itemX{screen_.getCenterX() - itemWidth / 2};
    const int itemY{getLocationOfFirstItem(count) + (getItemHeight() * item)};
    return {itemX, itemY};
}

std::pair<bool, int> Menu::getPointedItem(
    std::pair<int, int> mousePosition) const
{
    const int firstItem{
        getLocationOfFirstItem(static_cast<int>(items_.size()))};
    const auto [mouseX, mouseY] = mousePosition;
    const int itemWidth{getItemWidth()};
    const int itemHeight{getItemHeight()};
    for (int i = 0; i < static_cast<int>(items_.size()); ++i)
    {
        if ((mouseX > (screen_.getCenterX() - (itemWidth / 2))) &&
            (mouseX < (screen_.getCenterX() + (itemWidth / 2))) &&
            (mouseY > (firstItem + (itemHeight * i))) &&
            (mouseY < (firstItem + itemHeight + (itemHeight * i))))
            return {true, i};
    }
    return {false, 0};
}

UserChoice Menu::getUserChoice()
{
    Input input;
    for (int currentItem{0};;)
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
