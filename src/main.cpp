#include "Game.h"
#include "Input.h"
#include "Menu.h"
#include "Screen.h"

int main()
{
    Screen::init();
    Input::init();

    Screen screen({});
    Menu menu(screen);

    for (;;)
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
