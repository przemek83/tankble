#include <vector>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "Game.h"
#include "Menu.h"
#include "Screen.h"

static void initRandomGenerator()
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

static void setupGraphics()
{
    if (!al_init())
    {
        std::cerr << "failed to initialize allegro!\n" << std::endl;
        return;
    }

    al_install_keyboard();

    if (al_create_display(Config::width, Config::height) == nullptr)
    {
        std::cerr << "failed to create display!\n" << std::endl;
        return;
    }
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    al_init_image_addon();
    al_init_font_addon();

    al_set_window_title(al_get_current_display(), "TankBle");
    al_install_mouse();
}

int main()
{
    initRandomGenerator();
    setupGraphics();

    Resources resources;
    Screen screen(std::move(resources));
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
