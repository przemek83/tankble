#pragma once

#include <vector>

#include <allegro5/allegro.h>
#include "allegro5/allegro_font.h"

#include "game.h"

class Menu
{
public:
    Menu();
    ~Menu();

    void setMenuSize(int width, int height);

    enum Item : unsigned char
    {
        MAIN_MENU = 0,
        NEW_MENU,
        NEW_1P,
        OPTIONS_MENU,
        WINDOWED,
        FULLSCREEN,
        BACK,
        EXIT
    };

    Menu::Item getChoice();

private:
    Menu::Item loop();

    void drawMenuItems(unsigned int currentItem);

    unsigned int getCurrentItem(const ALLEGRO_EVENT& event,
                                unsigned int currentItem) const;

    bool userWantToExit(const ALLEGRO_EVENT& event) const;

    bool itemPicked(const ALLEGRO_EVENT& event) const;

    void redraw(unsigned int currentItem);

    bool escapePicked(const ALLEGRO_EVENT& event) const;

    Menu::Item getUserChoice(std::vector<std::pair<std::string, Item>> items);

    std::vector<std::pair<std::string, Menu::Item>> getMainMenu() const;

    std::vector<std::pair<std::string, Menu::Item>> getNewGameMenu() const;

    std::vector<std::pair<std::string, Menu::Item>> getOptionsMenu() const;

    ALLEGRO_BITMAP* menuBg_;
    ALLEGRO_BITMAP* itemBg_;
    ALLEGRO_BITMAP* itemBgSelect_;
    ALLEGRO_FONT* font_;
    int itemWidth_;
    int itemHeight_;
    int width_;
    int height_;
    int yTopItem_;
    std::vector<std::pair<std::string, Item>> items_;
};
