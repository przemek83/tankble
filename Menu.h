#pragma once

#include <string>
#include <vector>

#include "Input.h"

class Screen;

class Menu final
{
public:
    explicit Menu(Screen& screen);
    ~Menu() = default;

    Menu& operator=(const Menu& other) = delete;
    Menu(const Menu& other) = delete;

    Menu& operator=(Menu&& other) = delete;
    Menu(Menu&& other) = delete;

    enum class Item : unsigned char
    {
        NO_ITEM = 0,
        NEW_1P,
        WINDOWED,
        FULLSCREEN,
        EXIT
    };

    Menu::Item getItem();

private:
    enum class UserChoice : unsigned char
    {
        MAIN_MENU = 0,
        NEW_MENU,
        NEW_1P,
        OPTIONS_MENU,
        WINDOWED,
        FULLSCREEN,
        BACK,
        EXIT
    };

    void drawMenuItems(unsigned int currentItem);

    unsigned int getCurrentItem(Input input, Input::Action action,
                                unsigned int currentItem) const;

    bool itemPicked(const ALLEGRO_EVENT& event) const;

    void redraw(unsigned int currentItem);

    unsigned int getLocationOfFirstItem() const;

    unsigned int getItemWidth() const;

    unsigned int getItemHeight() const;

    UserChoice getUserChoice();

    std::vector<std::pair<std::string, Menu::UserChoice>> getMainMenu() const;

    std::vector<std::pair<std::string, Menu::UserChoice>> getNewGameMenu()
        const;

    std::vector<std::pair<std::string, Menu::UserChoice>> getOptionsMenu()
        const;

    std::pair<unsigned int, unsigned int> getItemPosition(unsigned int item);

    Screen& screen_;

    std::vector<std::pair<std::string, UserChoice>> items_{};
};
