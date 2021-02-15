#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include <vector>
#include "allegro5/allegro_font.h"
#include "game.h"

class Item
{
public:
    int (Game::*func)();
    const char* text;
    bool back;
    Item(int (Game::*pointer)(), const char* t, bool b = false);
    ~Item();
};

class Menu
{
public:
    Menu(int ws, int hs, int iw = 340, int ih = 70);
    ~Menu();
    void addItem(Item*);
    void draw(ALLEGRO_BITMAP*);
    int loop(ALLEGRO_BITMAP*, Game*);

private:
    void drawMenuItems(unsigned int selectedItem);

    unsigned int getSelectedItem(const ALLEGRO_EVENT& event,
                                 unsigned int currentSelectedItem) const;

    bool userWantToExit(const ALLEGRO_EVENT& event) const;

    bool itemPicked(const ALLEGRO_EVENT& event) const;

    void redraw(unsigned int selectedItem);

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
    std::vector<Item*> items;
    int check;
};

#endif

// end of menu.h
