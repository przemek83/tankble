#include <cstdlib>
#include <fstream>

#include "Config.h"
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
            return false;

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

    bool quit{false};
    while (!quit)
    {
        screen.showMouse();
        const UserChoice choice{getUserChoice(menu, input)};
        screen.hideMouse();

        if (choice == UserChoice::EXIT)
            return EXIT_SUCCESS;

        auto [ok, level]{Resources::getLevel(menu.choiceToLevel(choice))};
        if (!ok)
            return EXIT_FAILURE;

        Map map{Config::getInstance().getTileCount()};
        std::list<Tank> tanks{map.loadMap(level)};

        Game game{tanks, map};
        quit = play(std::move(game), screen, input);
    }

    return EXIT_SUCCESS;
}
