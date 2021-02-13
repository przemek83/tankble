#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include <vector>
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
private:
    ALLEGRO_BITMAP* menuBg;
    ALLEGRO_BITMAP* subMenuBg;
    ALLEGRO_BITMAP* itemBg;
    ALLEGRO_BITMAP* itemBgSelect;
    ALLEGRO_BITMAP* bmp;
    int itemWidth;
    int itemHeight;
    int itemCount;
    int widthScreen;
    int heightScreen;
    int yTopItem;
    std::vector<Item*> items;
    int check;

public:
    Menu(int ws, int hs, int iw = 340, int ih = 70);
    ~Menu();
    void addItem(Item*);
    void draw(ALLEGRO_BITMAP*);
    int loop(ALLEGRO_BITMAP*, Game*);
};

#endif

// end of menu.h
