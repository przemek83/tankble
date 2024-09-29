#include <cstdlib>

#include "Game.h"
#include "Input.h"
#include "Menu.h"
#include "Screen.h"

int main()
{
    Screen screen;
    if (!screen.init())
        return EXIT_FAILURE;

    Input::init();

    Menu menu(screen);

    while (true)
    {
        auto [play, level] = menu.playGame();
        if (!play)
            break;

        Game game(screen);
        if (!game.play(level))
            break;
    }

    return EXIT_SUCCESS;
}
