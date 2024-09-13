#include "Menu.h"

#include "Input.h"
#include "InputAction.h"
#include "Level.h"
#include "Screen.h"

Menu::Menu(Screen& screen) : screen_(screen), items_(getMainMenu()) {}

std::vector<std::pair<std::string, Menu::UserChoice>> Menu::getMainMenu()
{
    return {{"NEW GAME", UserChoice::LEVEL_MENU},
            {"OPTIONS", UserChoice::OPTIONS_MENU},
            {"EXIT", UserChoice::EXIT}};
}

std::vector<std::pair<std::string, Menu::UserChoice>> Menu::getNewGameMenu()
{
    return {{"LEVEL 1", UserChoice::LEVEL_1},
            {"LEVEL 2", UserChoice::LEVEL_2},
            {"LEVEL 3", UserChoice::LEVEL_3},
            {"LEVEL 4", UserChoice::LEVEL_4},
            {"BACK", UserChoice::BACK}};
}

std::vector<std::pair<std::string, Menu::UserChoice>> Menu::getOptionsMenu()
{
    return {{"FULL SCREEN", UserChoice::FULLSCREEN},
            {"WINDOWED", UserChoice::WINDOWED},
            {"BACK", UserChoice::BACK}};
}

std::pair<bool, Level> Menu::playGame()
{
    Screen::showMouse();

    for (;;)
    {
        switch (getUserChoice())
        {
            case UserChoice::MAIN_MENU:
            case UserChoice::BACK:
                items_ = getMainMenu();
                break;

            case UserChoice::LEVEL_MENU:
                items_ = getNewGameMenu();
                break;

            case UserChoice::OPTIONS_MENU:
                items_ = getOptionsMenu();
                break;

            case UserChoice::WINDOWED:
                screen_.useWindowedMode();
                break;

            case UserChoice::FULLSCREEN:
                screen_.useFullScreenMode();
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

Menu::UserChoice Menu::getUserChoice()
{
    Input input;
    for (int currentItem{0};;)
    {
        const InputAction action{input.getMenuAction()};

        if (action == InputAction::QUIT)
            return UserChoice::EXIT;

        if (action == InputAction::ACCEPT)
            return items_[static_cast<std::size_t>(currentItem)].second;

        if (action == InputAction::BACK)
            return items_[items_.size() - 1].second;

        currentItem =
            getCurrentItem(input.getMousePosition(), action, currentItem);

        if (action == InputAction::TIMER)
            redraw(currentItem);
    }
}

void Menu::drawMenuItem(int item, ResourceType resource)
{
    const auto itemHeight{static_cast<float>(getItemHeight())};
    const auto [itemX, itemY]{getItemPosition(item)};
    screen_.drawScaledBitmap(resource, itemX, itemY, getItemWidth(),
                             getItemHeight());
    const auto itemMiddleY{itemY + static_cast<int>(itemHeight / 2.F)};
    screen_.drawText(screen_.getCenterX(), itemMiddleY,
                     items_[static_cast<std::size_t>(item)].first);
}

void Menu::drawMenuItems(int currentItem)
{
    for (int item = 0; item < static_cast<int>(items_.size()); ++item)
    {
        ResourceType resource{ResourceType::MENU_ITEM};
        if (item == currentItem)
            resource = ResourceType::MENU_ITEM_SELECTED;

        drawMenuItem(item, resource);
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

int Menu::getLocationOfFirstItem() const
{
    return screen_.getCenterY() -
           (static_cast<int>(items_.size()) * getItemHeight() / 2);
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

std::pair<int, int> Menu::getItemPosition(int item) const
{
    const int itemWidth{getItemWidth()};
    const int itemX{screen_.getCenterX() - itemWidth / 2};
    const int itemY{getLocationOfFirstItem() + (getItemHeight() * item)};
    return {itemX, itemY};
}

std::pair<bool, int> Menu::getPointedItem(
    std::pair<int, int> mousePosition) const
{
    const int firstItem{getLocationOfFirstItem()};
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
