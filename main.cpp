#include <vector>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "game.h"
#include "menu.h"

static void setupAllegro()
{
    if (!al_init())
    {
        std::cerr << "failed to initialize allegro!\n" << std::endl;
        return;
    }

    al_install_keyboard();

    al_set_new_display_option(ALLEGRO_COLOR_SIZE, 32, ALLEGRO_REQUIRE);
    if (al_create_display(WIDTH, HEIGHT) == nullptr)
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
    std::cout << "start" << std::endl;

    srand((unsigned)time(0));
    setupAllegro();

    Menu menu(800, 600);

    std::vector<std::pair<std::string, Menu::Item>> mainMenu{
        {"NEW GAME", Menu::Item::NEW_MENU},
        {"OPTIONS", Menu::Item::OPTIONS_MENU},
        {"EXIT", Menu::Item::EXIT}};

    std::vector<std::pair<std::string, Menu::Item>> newGameMenu{
        {"1 PLAYER", Menu::Item::NEW_1P}, {"BACK", Menu::Item::BACK}};

    std::vector<std::pair<std::string, Menu::Item>> optionsMenu{
        {"FULL SCREEN", Menu::Item::FULLSCREEN},
        {"WINDOWED", Menu::Item::WINDOWED},
        {"BACK", Menu::Item::BACK}};

    al_show_mouse_cursor(al_get_current_display());
    Menu::Item userChoice{Menu::Item::MAIN_MENU};
    while (userChoice != Menu::Item::EXIT)
    {
        switch (userChoice)
        {
            case Menu::Item::MAIN_MENU:
            case Menu::Item::BACK:
                userChoice = menu.getUserChoice(mainMenu);
                break;

            case Menu::Item::NEW_MENU:
                userChoice = menu.getUserChoice(newGameMenu);
                break;

            case Menu::Item::OPTIONS_MENU:
                userChoice = menu.getUserChoice(optionsMenu);
                break;

            case Menu::Item::FULLSCREEN:
                setFullScreenMode();
                userChoice = menu.getUserChoice(optionsMenu);
                break;

            case Menu::Item::WINDOWED:
                setWindowedMode();
                userChoice = menu.getUserChoice(optionsMenu);
                break;

            case Menu::Item::NEW_1P:
            {
                al_hide_mouse_cursor(al_get_current_display());
                Game game;
                game.startGame();
                al_show_mouse_cursor(al_get_current_display());
                userChoice = menu.getUserChoice(newGameMenu);
                break;
            }

            case Menu::Item::EXIT:
                break;
        }
    }
    al_hide_mouse_cursor(al_get_current_display());

    std::cout << "end" << std::endl;

    return 0;
}
