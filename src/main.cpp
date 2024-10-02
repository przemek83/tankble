#include <cstdlib>

#include "Game.h"
#include "Input.h"
#include "Menu.h"
#include "Screen.h"
#include "UserChoice.h"

namespace
{
UserChoice getUserChoice(Menu& menu)
{
    UserChoice choice{UserChoice::MAIN_MENU};
    Input input;
    while ((choice != UserChoice::EXIT) && (!menu.isLevelPicked(choice)))
    {
        menu.refresh(choice);
        choice = menu.getUserChoice(input);
    }
    return choice;
}
};  // namespace

int main()
{
    Screen screen;
    if (!screen.init())
        return EXIT_FAILURE;

    Input::init();

    Menu menu(screen);

    while (true)
    {
        screen.showMouse();
        const UserChoice choice{getUserChoice(menu)};
        screen.hideMouse();

        if (choice == UserChoice::EXIT)
            return EXIT_SUCCESS;

        Game game(screen);
        if (!game.play(menu.choiceToLevel(choice)))
            return EXIT_SUCCESS;
    }
}
