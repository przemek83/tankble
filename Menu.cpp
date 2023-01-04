#include "Menu.h"

#include "Screen.h"

Menu::Menu(Screen& screen) : screen_(screen) { items_ = getMainMenu(); }

std::vector<std::pair<std::string, Menu::UserChoice>> Menu::getMainMenu() const
{
    return {{"NEW GAME", UserChoice::NEW_MENU},
            {"OPTIONS", UserChoice::OPTIONS_MENU},
            {"EXIT", UserChoice::EXIT}};
}

std::vector<std::pair<std::string, Menu::UserChoice>> Menu::getNewGameMenu()
    const
{
    return {{"1 PLAYER", UserChoice::NEW_1P}, {"BACK", UserChoice::BACK}};
}

std::vector<std::pair<std::string, Menu::UserChoice>> Menu::getOptionsMenu()
    const
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
        Input::Action action{input.getAction()};

        if (action == Input::Action::QUIT)
            return UserChoice::EXIT;

        if (action == Input::Action::ACCEPT)
            return items_[currentItem].second;

        if (action == Input::Action::BACK)
            return items_[items_.size() - 1].second;

        currentItem = getCurrentItem(input, action, currentItem);

        if (action == Input::Action::TIMER)
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
        Resources::Bitmap itemBitmap;
        if (item == currentItem)
            itemBitmap = Resources::Bitmap::MENU_ITME_SELECTED;
        else
            itemBitmap = Resources::Bitmap::MENU_ITEM;

        const auto [itemX, itemY]{getItemPosition(item)};
        screen_.drawBitmap(itemBitmap, itemX, itemY);
        const auto itemMiddleY{
            static_cast<unsigned int>(itemY + itemHeight / 2.F)};
        screen_.drawText(screen_.getCenterX(), itemMiddleY, items_[item].first);
    }
}

unsigned int Menu::getCurrentItem(Input input, Input::Action action,
                                  unsigned int currentItem) const
{
    if (action == Input::Action::UP && currentItem > 0)
        return currentItem - 1;

    if (action == Input::Action::DOWN &&
        currentItem < static_cast<unsigned int>(items_.size()) - 1)
        return currentItem + 1;

    if (action == Input::Action::MOUSE_MOVE)
    {
        const unsigned int firstItem{getLocationOfFirstItem()};
        const auto [mouseX, mouseY] = input.getMousePosition();
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
    screen_.drawBackground(Resources::Bitmap::BACKGROUND);
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
    return screen_.getBitmapWidth(Resources::Bitmap::MENU_ITEM);
}

unsigned int Menu::getItemHeight() const
{
    return screen_.getBitmapHeight(Resources::Bitmap::MENU_ITEM);
}

std::pair<unsigned int, unsigned int> Menu::getItemPosition(unsigned int item)
{
    const unsigned int itemWidth{getItemWidth()};
    const unsigned int itemX{screen_.getCenterX() - itemWidth / 2};
    const unsigned int itemY{getLocationOfFirstItem() +
                             (getItemHeight() * item)};
    return {itemX, itemY};
}
