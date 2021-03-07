#pragma once

#include <vector>

#include <allegro5/allegro.h>
#include "allegro5/allegro_font.h"

#include "game.h"

class Menu
{
public:
    Menu(unsigned int width, unsigned int height);
    ~Menu();

    void setMenuSize(unsigned int width, unsigned int height);

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

    unsigned int getLocationOfFirstItem() const;

    unsigned int getItemWidth() const;

    unsigned int getItemHeight() const;

    Menu::Item getUserChoice(std::vector<std::pair<std::string, Item>> items);

    std::vector<std::pair<std::string, Menu::Item>> getMainMenu() const;

    std::vector<std::pair<std::string, Menu::Item>> getNewGameMenu() const;

    std::vector<std::pair<std::string, Menu::Item>> getOptionsMenu() const;

    std::pair<ALLEGRO_EVENT_QUEUE*, ALLEGRO_TIMER*> sutupEventQueueAndTimer()
        const;

    ALLEGRO_BITMAP* menuBg_;
    ALLEGRO_BITMAP* itemBg_;
    ALLEGRO_BITMAP* itemBgSelect_;
    ALLEGRO_FONT* font_;
    unsigned int width_{0};
    unsigned int height_{0};
    std::vector<std::pair<std::string, Item>> items_{};
};
