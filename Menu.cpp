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
        }
    }
}

Menu::UserChoice Menu::getUserChoice()
{
    Input input;
    for (unsigned int currentItem{0};;)
    {
        const InputAction action{input.getMenuAction()};

        if (action == InputAction::QUIT)
            return UserChoice::EXIT;

        if (action == InputAction::ACCEPT)
            return items_[currentItem].second;

        if (action == InputAction::BACK)
            return items_[items_.size() - 1].second;

        currentItem =
            getCurrentItem(input.getMousePosition(), action, currentItem);

        if (action == InputAction::TIMER)
            redraw(currentItem);
    }
}

void Menu::drawMenuItems(unsigned int currentItem)
{
    const auto itemHeight{static_cast<float>(getItemHeight())};
    for (unsigned int item = 0; item < items_.size(); item++)
    {
        ResourceType itemResource{ResourceType::MENU_ITEM};
        if (item == currentItem)
            itemResource = ResourceType::MENU_ITME_SELECTED;

        const auto [itemX, itemY]{getItemPosition(item)};
        screen_.drawBitmap(itemResource, itemX, itemY);
        const auto itemMiddleY{itemY +
                               static_cast<unsigned int>(itemHeight / 2.F)};
        screen_.drawText(screen_.getCenterX(), itemMiddleY, items_[item].first);
    }
}

unsigned int Menu::getCurrentItem(
    std::pair<unsigned int, unsigned int> mousePosition, InputAction action,
    unsigned int currentItem) const
{
    if (action == InputAction::UP && currentItem > 0)
        return currentItem - 1;

    if (action == InputAction::DOWN &&
        currentItem < static_cast<unsigned int>(items_.size()) - 1)
        return currentItem + 1;

    if (action == InputAction::MOUSE_MOVE)
    {
        const unsigned int firstItem{getLocationOfFirstItem()};
        const auto [mouseX, mouseY] = mousePosition;
        const unsigned int itemWidth{getItemWidth()};
        const unsigned int itemHeight{getItemHeight()};
        for (unsigned int i = 0; i < items_.size(); i++)
        {
            if ((mouseX > screen_.getCenterX() - itemWidth / 2) &&
                (mouseX < screen_.getCenterX() + itemWidth / 2) &&
                (mouseY > firstItem + itemHeight * i) &&
                (mouseY < firstItem + itemHeight + itemHeight * i))
                return i;
        }
    }

    return currentItem;
}

void Menu::redraw(unsigned int currentItem)
{
    screen_.drawBackground(ResourceType::BACKGROUND);
    drawMenuItems(currentItem);
    Screen::refresh();
}

unsigned int Menu::getLocationOfFirstItem() const
{
    return screen_.getCenterY() -
           static_cast<unsigned int>(items_.size()) * getItemHeight() / 2;
}

unsigned int Menu::getItemWidth() const
{
    return screen_.getBitmapWidth(ResourceType::MENU_ITEM);
}

unsigned int Menu::getItemHeight() const
{
    return screen_.getBitmapHeight(ResourceType::MENU_ITEM);
}

std::pair<unsigned int, unsigned int> Menu::getItemPosition(unsigned int item)
{
    const unsigned int itemWidth{getItemWidth()};
    const unsigned int itemX{screen_.getCenterX() - itemWidth / 2};
    const unsigned int itemY{getLocationOfFirstItem() +
                             (getItemHeight() * item)};
    return {itemX, itemY};
}
