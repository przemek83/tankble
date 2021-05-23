#pragma once

#include <vector>

#include <allegro5/allegro.h>
#include "allegro5/allegro_font.h"

#include "game.h"

class Screen;

class Menu final
{
public:
    Menu(Screen& screen);
    ~Menu();

    Menu& operator=(const Menu& other) = delete;
    Menu(const Menu& other) = delete;

    Menu& operator=(Menu&& other) = delete;
    Menu(Menu&& other) = delete;

    enum class Item : unsigned char
    {
        NO_ITEM = 0,
        NEW_1P,
        WINDOWED,
        FULLSCREEN,
        EXIT
    };

    Menu::Item getItem();

private:
    enum class UserChoice : unsigned char
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

    void drawMenuItems(unsigned int currentItem);

    unsigned int getCurrentItem(const ALLEGRO_EVENT& event,
                                unsigned int currentItem) const;

    bool userWantToExit(const ALLEGRO_EVENT& event) const;

    bool itemPicked(const ALLEGRO_EVENT& event) const;

    void redraw(unsigned int currentItem);

    unsigned int getLocationOfFirstItem() const;

    unsigned int getItemWidth() const;

    unsigned int getItemHeight() const;

    UserChoice getUserChoice();

    std::vector<std::pair<std::string, Menu::UserChoice>> getMainMenu() const;

    std::vector<std::pair<std::string, Menu::UserChoice>> getNewGameMenu()
        const;

    std::vector<std::pair<std::string, Menu::UserChoice>> getOptionsMenu()
        const;

    std::pair<ALLEGRO_EVENT_QUEUE*, ALLEGRO_TIMER*> sutupEventQueueAndTimer()
        const;

    std::pair<float, float> getItemPositionFloat(unsigned int item);

    bool keyEscapeUsed(const ALLEGRO_EVENT& event) const;

    bool keyUpUsed(const ALLEGRO_EVENT& event) const;

    bool keyDownUsed(const ALLEGRO_EVENT& event) const;

    bool keyEnterUsed(const ALLEGRO_EVENT& event) const;

    bool keySpaceUsed(const ALLEGRO_EVENT& event) const;

    bool mouseClickUsed(const ALLEGRO_EVENT& event) const;

    Screen& screen_;

    ALLEGRO_BITMAP* menuBg_;
    ALLEGRO_BITMAP* itemBg_;
    ALLEGRO_BITMAP* itemBgSelect_;
    std::vector<std::pair<std::string, UserChoice>> items_{};
};
