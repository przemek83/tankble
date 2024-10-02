#pragma once

#include <vector>

#include "MenuItem.h"

class display;
enum class InputAction : char;
enum class Level : char;
enum class UserChoice : char;
class Input;

class Menu final
{
public:
    explicit Menu(Display& display);

    UserChoice getUserChoice(Input& input);

    void refresh(UserChoice choice);

    bool isLevelPicked(UserChoice choice) const;

    Level choiceToLevel(UserChoice choice) const;

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

    Display& display_;

    std::vector<MenuItem> items_;
};
