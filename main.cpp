#include <vector>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

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

static void updateMenuSize(Menu& menu)
{
    menu.setMenuSize(static_cast<unsigned int>(
                         al_get_display_width(al_get_current_display())),
                     static_cast<unsigned int>(
                         al_get_display_height(al_get_current_display())));
}

int main()
{
    initRandomGenerator();
    setupAllegro();

    Menu menu(Config::width, Config::height);
    Menu::Item choice{Menu::Item::BACK};
    while (choice != Menu::Item::EXIT)
    {
        choice = menu.getChoice();
        switch (choice)
        {
            case Menu::Item::NEW_1P:
            {
                Game game;
                game.startGame();
                break;
            }

            case Menu::Item::WINDOWED:
                setWindowedMode();
                updateMenuSize(menu);
                break;

            case Menu::Item::FULLSCREEN:
                setFullScreenMode();
                updateMenuSize(menu);
                break;

            default:
            case Menu::Item::EXIT:
                break;
        }
    }
    return 0;
}
