#include "Menu.h"

#include "Input.h"
#include "InputAction.h"
#include "Screen.h"

Menu::Menu(Screen& screen) : screen_(screen), items_(getMainMenu()) {}

std::vector<std::pair<std::string, Menu::UserChoice>> Menu::getMainMenu()
{
    return {{"NEW GAME", UserChoice::NEW_MENU},
            {"OPTIONS", UserChoice::OPTIONS_MENU},
            {"EXIT", UserChoice::EXIT}};
}

std::vector<std::pair<std::string, Menu::UserChoice>> Menu::getNewGameMenu()
{
    return {{"1 PLAYER", UserChoice::NEW_1P}, {"BACK", UserChoice::BACK}};
}

std::vector<std::pair<std::string, Menu::UserChoice>> Menu::getOptionsMenu()
{
    return {{"FULL SCREEN", UserChoice::FULLSCREEN},
            {"WINDOWED", UserChoice::WINDOWED},
            {"BACK", UserChoice::BACK}};
}

bool Menu::playGame()
{
    screen_.showMouse();

    for (;;)
    {
        switch (getUserChoice())
        {
            case UserChoice::MAIN_MENU:
            case UserChoice::BACK:
                items_ = getMainMenu();
                break;

            case UserChoice::NEW_MENU:
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
                screen_.hideMouse();
                return false;

            case UserChoice::NEW_1P:
                screen_.hideMouse();
                return true;
        }
    }
}

Menu::UserChoice Menu::getUserChoice()
{
    Input input;
    bool shouldRedraw{true};
    for (unsigned int currentItem{0};;)
    {
        const InputAction action{input.getAction()};

        if (action == InputAction::QUIT)
            return UserChoice::EXIT;

        if (action == InputAction::ACCEPT)
            return items_[currentItem].second;

        if (action == InputAction::BACK)
            return items_[items_.size() - 1].second;

        currentItem =
            getCurrentItem(input.getMousePosition(), action, currentItem);

        if (action == InputAction::TIMER)
            shouldRedraw = true;

        if (shouldRedraw && input.isEmpty())
        {
            shouldRedraw = false;
            redraw(currentItem);
        }
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
    screen_.refresh();
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
