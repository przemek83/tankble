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

bool play(Game game, Display& display, Input& input)
{
    display.clearScreenWithBlack();

    while (true)
    {
        const InputAction action{input.getMenuAction()};
        if ((action == InputAction::BACK) || (game.isGameEnding(display)))
            break;

        if (action == InputAction::QUIT)
            return true;

        if (action == InputAction::TIMER)
        {
            game.draw(display);
            game.moveBullets();
            game.movePlayerTank(input.getGameActions());
            game.moveEnemyTanks();
            display.refresh();
        }
    }

    return false;
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

    bool exit{false};
    while (!exit)
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

        exit = play(std::move(game), screen, input);
    }
}
