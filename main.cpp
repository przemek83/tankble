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

static std::vector<std::pair<std::string, Menu::Item>> getMainMenu()
{
    return {{"NEW GAME", Menu::Item::NEW_MENU},
            {"OPTIONS", Menu::Item::OPTIONS_MENU},
            {"EXIT", Menu::Item::EXIT}};
}

static std::vector<std::pair<std::string, Menu::Item>> getNewGameMenu()
{
    return {{"1 PLAYER", Menu::Item::NEW_1P}, {"BACK", Menu::Item::BACK}};
}

static std::vector<std::pair<std::string, Menu::Item>> getOptionsMenu()
{
    return {{"FULL SCREEN", Menu::Item::FULLSCREEN},
            {"WINDOWED", Menu::Item::WINDOWED},
            {"BACK", Menu::Item::BACK}};
}

static void updateMenuSize(Menu& menu)
{
    menu.setMenuSize(al_get_display_width(al_get_current_display()),
                     al_get_display_height(al_get_current_display()));
}

static bool userWantsToPlayAGame()
{
    Menu menu;

    al_show_mouse_cursor(al_get_current_display());
    Menu::Item userChoice{Menu::Item::MAIN_MENU};
    while (userChoice != Menu::Item::EXIT && userChoice != Menu::Item::NEW_1P)
    {
        switch (userChoice)
        {
            case Menu::Item::MAIN_MENU:
            case Menu::Item::BACK:
                userChoice = menu.getUserChoice(getMainMenu());
                break;

            case Menu::Item::NEW_MENU:
                userChoice = menu.getUserChoice(getNewGameMenu());
                break;

            case Menu::Item::OPTIONS_MENU:
                userChoice = menu.getUserChoice(getOptionsMenu());
                break;

            case Menu::Item::FULLSCREEN:
                setFullScreenMode();
                updateMenuSize(menu);
                userChoice = menu.getUserChoice(getOptionsMenu());
                break;

            case Menu::Item::WINDOWED:
                setWindowedMode();
                updateMenuSize(menu);
                userChoice = menu.getUserChoice(getOptionsMenu());
                break;

            case Menu::Item::EXIT:
            case Menu::Item::NEW_1P:;
        }
    }
    al_hide_mouse_cursor(al_get_current_display());
    return userChoice == Menu::Item::NEW_1P;
}

int main()
{
    initRandomGenerator();
    setupAllegro();

    while (userWantsToPlayAGame())
    {
        Game game;
        game.startGame();
    }
    return 0;
}
