#pragma once

#include <vector>

#include "MenuItem.h"
#include "UserChoice.h"

class Screen;
enum class InputAction : char;
enum class Level : char;
class MenuItem;

class Menu final
{
public:
    explicit Menu(Screen& screen);

    std::pair<bool, Level> playGame();

private:
    void drawMenuItems(int currentItem);

    int getCurrentItem(std::pair<int, int> mousePosition, InputAction action,
                       int currentItem) const;

    void redraw(int currentItem);

    void initMenu(std::vector<UserChoice> userChoices);

    void initMainMenu();

    void initNewGameMenu();

    void initOptionsMenu();

    bool mouseIsHoveringItem(std::pair<int, int> mousePosition, int item) const;

    std::pair<bool, int> getPointedItem(
        std::pair<int, int> mousePosition) const;

    UserChoice getUserChoice();

    Screen& screen_;

    std::vector<MenuItem> items_;
};
