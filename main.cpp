#include <vector>

#include "Game.h"
#include "Input.h"
#include "Menu.h"
#include "Screen.h"

static void initRandomGenerator()
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

int main()
{
    initRandomGenerator();

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

    return 0;
}
