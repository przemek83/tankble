#pragma once

#include <string>
#include <vector>

class Screen;
union ALLEGRO_EVENT;
struct ALLEGRO_EVENT_QUEUE;
struct ALLEGRO_TIMER;

class Menu final
{
public:
    explicit Menu(Screen& screen);
    ~Menu() = default;

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

    std::pair<unsigned int, unsigned int> getItemPosition(unsigned int item);

    bool keyEscapeUsed(const ALLEGRO_EVENT& event) const;

    bool keyUpUsed(const ALLEGRO_EVENT& event) const;

    bool keyDownUsed(const ALLEGRO_EVENT& event) const;

    bool keyEnterUsed(const ALLEGRO_EVENT& event) const;

    bool keySpaceUsed(const ALLEGRO_EVENT& event) const;

    bool mouseClickUsed(const ALLEGRO_EVENT& event) const;

    Screen& screen_;

    std::vector<std::pair<std::string, UserChoice>> items_{};
};
