#pragma once

#include <string>
#include <vector>

class Screen;
union ALLEGRO_EVENT;
enum class InputAction : unsigned char;

class Menu final
{
public:
    explicit Menu(Screen& screen);

    bool playGame();

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

    unsigned int getCurrentItem(
        std::pair<unsigned int, unsigned int> mousePosition, InputAction action,
        unsigned int currentItem) const;

    bool itemPicked(const ALLEGRO_EVENT& event) const;

    void redraw(unsigned int currentItem);

    unsigned int getLocationOfFirstItem() const;

    unsigned int getItemWidth() const;

    unsigned int getItemHeight() const;

    UserChoice getUserChoice();

    static std::vector<std::pair<std::string, Menu::UserChoice>> getMainMenu();

    static std::vector<std::pair<std::string, Menu::UserChoice>>
    getNewGameMenu();

    static std::vector<std::pair<std::string, Menu::UserChoice>>
    getOptionsMenu();

    std::pair<unsigned int, unsigned int> getItemPosition(unsigned int item);

    Screen& screen_;

    std::vector<std::pair<std::string, UserChoice>> items_{};
};
