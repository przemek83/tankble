#include <cstdlib>
#include <fstream>

#include "Game.h"
#include "InputAction.h"
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

        Game game;
        const Level level{menu.choiceToLevel(choice)};
        if (auto [ok, levelContent]{Resources::getLevel(level)}; ok)
            game.init(levelContent);
        else
            return EXIT_FAILURE;

        screen.clearScreenWithBlack();

        while (true)
        {
            const InputAction action{input.getMenuAction()};
            if ((action == InputAction::BACK) || (game.isGameEnding(screen)))
                break;

            if (action == InputAction::QUIT)
                return EXIT_SUCCESS;

            if (action == InputAction::TIMER)
            {
                game.draw(screen);
                const std::set<InputAction> actions{input.getGameActions()};
                game.control(actions);
                screen.refresh();
            }
        }
    }
}
