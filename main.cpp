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
        if (!menu.playGame())
            break;

        Game game(screen);
        if (!game.play())
            break;
    }

    return EXIT_SUCCESS;
}
