#pragma once

#include <string>
#include <vector>

class Screen;
enum class InputAction : unsigned char;
enum class Level : unsigned char;

class Menu final
{
public:
    explicit Menu(Screen& screen);

    std::pair<bool, Level> playGame();

private:
    enum class UserChoice : unsigned char
    {
        MAIN_MENU = 0,
        LEVEL_MENU,
        LEVEL_1,
        LEVEL_2,
        LEVEL_3,
        LEVEL_4,
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

    void redraw(unsigned int currentItem);

    unsigned int getLocationOfFirstItem() const;

    int getItemWidth() const;

    int getItemHeight() const;

    UserChoice getUserChoice();

    static std::vector<std::pair<std::string, Menu::UserChoice>> getMainMenu();

    static std::vector<std::pair<std::string, Menu::UserChoice>>
    getNewGameMenu();

    static std::vector<std::pair<std::string, Menu::UserChoice>>
    getOptionsMenu();

    std::pair<unsigned int, unsigned int> getItemPosition(
        unsigned int item) const;

    Screen& screen_;

    std::vector<std::pair<std::string, UserChoice>> items_{};
};
