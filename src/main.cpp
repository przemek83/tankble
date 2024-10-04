#include <cstdlib>

#include "Game.h"
#include "Menu.h"
#include "Screen.h"
#include "StandardInput.h"
#include "UserChoice.h"

namespace
{
UserChoice getUserChoice(Menu& menu, Input& input)
{
    UserChoice choice{UserChoice::MAIN_MENU};
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

    StandardInput::init();
    StandardInput input;

    Menu menu(screen);

    while (true)
    {
        screen.showMouse();
        const UserChoice choice{getUserChoice(menu, input)};
        screen.hideMouse();

        if (choice == UserChoice::EXIT)
            return EXIT_SUCCESS;

        Game game(screen);
        if (!game.init(menu.choiceToLevel(choice)))
            return EXIT_FAILURE;

        if (!game.play(input))
            return EXIT_SUCCESS;
    }
}
