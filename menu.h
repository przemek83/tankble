#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include <vector>
#include "allegro5/allegro_font.h"
#include "game.h"

// class Item
//{
// public:
//    int (Game::*func)();
//    const char* text;
//    bool back;
//    Item(int (Game::*pointer)(), const char* t, bool b = false);
//    ~Item();
//};

class Menu
{
public:
    Menu(int ws, int hs, int iw = 340, int ih = 70);
    ~Menu();

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

    Menu::Item getUserChoice(std::vector<std::pair<std::string, Item>> items);

private:
    Menu::Item loop();

    void drawMenuItems(unsigned int currentItem);

    unsigned int getCurrentItem(const ALLEGRO_EVENT& event,
                                unsigned int currentItem) const;

    bool userWantToExit(const ALLEGRO_EVENT& event) const;

    bool itemPicked(const ALLEGRO_EVENT& event) const;

    void redraw(unsigned int currentItem);

    ALLEGRO_BITMAP* menuBg;
    ALLEGRO_BITMAP* subMenuBg;
    ALLEGRO_BITMAP* itemBg;
    ALLEGRO_BITMAP* itemBgSelect;
    ALLEGRO_BITMAP* bmp;
    ALLEGRO_FONT* font;
    int itemWidth;
    int itemHeight;
    int itemCount;
    int widthScreen;
    int heightScreen;
    int yTopItem;
    std::vector<std::pair<std::string, Item>> items_;
    // std::vector<Item*> items;
    int check;
};

#endif

// end of menu.h
