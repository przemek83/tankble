#include <vector>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "Screen.h"
#include "game.h"
#include "menu.h"

static void initRandomGenerator()
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

static void setupAllegro()
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

static void setFullScreenMode()
{
    al_set_display_flag(al_get_current_display(), ALLEGRO_FULLSCREEN_WINDOW,
                        true);
}

static void setWindowedMode()
{
    al_set_display_flag(al_get_current_display(), ALLEGRO_FULLSCREEN_WINDOW,
                        false);
}

int main()
{
    initRandomGenerator();
    setupAllegro();

    Resources resources;
    Screen screen(std::move(resources));
    Menu menu(screen);
    for (Menu::Item choice{menu.getItem()}; choice != Menu::Item::EXIT;
         choice = menu.getItem())
    {
        switch (choice)
        {
            case Menu::Item::NEW_1P:
            {
                Game game(screen);
                game.startGame();
                break;
            }

            case Menu::Item::WINDOWED:
                setWindowedMode();
                screen.updateSize();
                break;

            case Menu::Item::FULLSCREEN:
                setFullScreenMode();
                screen.updateSize();
                break;

            case Menu::Item::EXIT:
            case Menu::Item::NO_ITEM:
                break;
        }
    }
    return 0;
}
