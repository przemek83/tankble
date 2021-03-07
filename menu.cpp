#include "menu.h"
#include "config.h"
#include "game.h"

Menu::Menu() : font_(al_create_builtin_font())
{
    itemBg_ = al_load_bitmap("image/menu/item.tga");
    itemBgSelect_ = al_load_bitmap("image/menu/item_select.tga");
    menuBg_ = al_load_bitmap("image/menu/background.bmp");

    setMenuSize(WIDTH, HEIGHT);

    yTopItem_ = 0;

    items_ = getMainMenu();
}

Menu::~Menu()
{
    al_destroy_bitmap(itemBg_);
    al_destroy_bitmap(itemBgSelect_);
    al_destroy_bitmap(menuBg_);
}

void Menu::setMenuSize(int width, int height)
{
    width_ = width;
    height_ = height;
    itemWidth_ = al_get_bitmap_width(itemBg_);
    itemHeight_ = al_get_bitmap_height(itemBg_);
}

std::vector<std::pair<std::string, Menu::Item>> Menu::getMainMenu() const
{
    return {{"NEW GAME", Menu::Item::NEW_MENU},
            {"OPTIONS", Menu::Item::OPTIONS_MENU},
            {"EXIT", Menu::Item::EXIT}};
}

std::vector<std::pair<std::string, Menu::Item>> Menu::getNewGameMenu() const
{
    return {{"1 PLAYER", Menu::Item::NEW_1P}, {"BACK", Menu::Item::BACK}};
}

std::vector<std::pair<std::string, Menu::Item>> Menu::getOptionsMenu() const
{
    return {{"FULL SCREEN", Menu::Item::FULLSCREEN},
            {"WINDOWED", Menu::Item::WINDOWED},
            {"BACK", Menu::Item::BACK}};
}

Menu::Item Menu::getChoice()
{
    al_show_mouse_cursor(al_get_current_display());
    while (true)
    {
        const Menu::Item userChoice{getUserChoice(items_)};
        switch (userChoice)
        {
            case Menu::Item::MAIN_MENU:
            case Menu::Item::BACK:
                items_ = getMainMenu();
                break;

            case Menu::Item::NEW_MENU:
                items_ = getNewGameMenu();
                break;

            case Menu::Item::OPTIONS_MENU:
                items_ = getOptionsMenu();
                break;

            case Menu::Item::WINDOWED:
            case Menu::Item::FULLSCREEN:
                items_ = getOptionsMenu();
                return userChoice;

            case Menu::Item::EXIT:
            case Menu::Item::NEW_1P:
                al_hide_mouse_cursor(al_get_current_display());
                return userChoice;
        }
    }
}

Menu::Item Menu::getUserChoice(std::vector<std::pair<string, Item>> items)
{
    items_ = std::move(items);
    yTopItem_ = height_ / 2 - items_.size() * itemHeight_ / 2;
    return loop();
}

void Menu::drawMenuItems(unsigned int currentItem)
{
    for (unsigned int i = 0; i < items_.size(); i++)
    {
        ALLEGRO_BITMAP* itemBitmap{nullptr};
        if (i == currentItem)
            itemBitmap = itemBgSelect_;
        else
            itemBitmap = itemBg_;
        al_draw_bitmap_region(itemBitmap, 0, 0, itemWidth_, itemHeight_,
                              width_ / 2 - itemWidth_ / 2,
                              yTopItem_ + itemHeight_ * i, 0);
        al_draw_text(font_, al_map_rgb(255, 255, 255), width_ / 2,
                     yTopItem_ + itemHeight_ * i + itemHeight_ / 2,
                     ALLEGRO_ALIGN_CENTER, items_[i].first.c_str());
    }
}

unsigned int Menu::getCurrentItem(const ALLEGRO_EVENT& event,
                                  unsigned int currentItem) const
{
    if (event.type == ALLEGRO_EVENT_KEY_UP &&
        event.keyboard.keycode == ALLEGRO_KEY_UP && currentItem > 0)
        return currentItem - 1;

    if (event.type == ALLEGRO_EVENT_KEY_UP &&
        event.keyboard.keycode == ALLEGRO_KEY_DOWN &&
        currentItem < static_cast<unsigned int>(items_.size()) - 1)
        return currentItem + 1;

    if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        for (unsigned int i = 0; i < items_.size(); i++)
        {
            if ((event.mouse.x > width_ / 2 - itemWidth_ / 2) &&
                (event.mouse.x < width_ / 2 + itemWidth_ / 2) &&
                (event.mouse.y > yTopItem_ + itemHeight_ * i) &&
                (event.mouse.y < yTopItem_ + itemHeight_ + itemHeight_ * i))
                return i;
        }
    }

    return currentItem;
}

bool Menu::userWantToExit(const ALLEGRO_EVENT& event) const
{
    return event.type == ALLEGRO_EVENT_DISPLAY_CLOSE;
}

bool Menu::itemPicked(const ALLEGRO_EVENT& event) const
{
    if (event.type == ALLEGRO_EVENT_KEY_UP &&
        (event.keyboard.keycode == ALLEGRO_KEY_ENTER ||
         event.keyboard.keycode == ALLEGRO_KEY_SPACE))
        return true;

    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 1)
        return true;

    return false;
}

void Menu::redraw(unsigned int currentItem)
{
    al_clear_to_color(al_map_rgb_f(0, 0, 0));
    al_draw_scaled_bitmap(menuBg_, 0, 0, al_get_bitmap_width(menuBg_),
                          al_get_bitmap_height(menuBg_), 0, 0, width_, height_,
                          0);
    drawMenuItems(currentItem);
    al_flip_display();
}

bool Menu::escapePicked(const ALLEGRO_EVENT& event) const
{
    return event.type == ALLEGRO_EVENT_KEY_UP &&
           event.keyboard.keycode == ALLEGRO_KEY_ESCAPE;
}

std::pair<ALLEGRO_EVENT_QUEUE*, ALLEGRO_TIMER*> Menu::sutupEventQueueAndTimer()
    const
{
    ALLEGRO_EVENT_QUEUE* events{al_create_event_queue()};
    ALLEGRO_TIMER* timer{al_create_timer(1.0 / Config::fps)};
    al_register_event_source(events, al_get_keyboard_event_source());
    al_register_event_source(events, al_get_mouse_event_source());
    al_register_event_source(
        events, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(events, al_get_timer_event_source(timer));
    al_start_timer(timer);
    return {events, timer};
}

Menu::Item Menu::loop()
{
    auto [eventsQueue, timer]{sutupEventQueueAndTimer()};
    bool shouldRedraw{true};
    unsigned int currentItem{0};
    while (true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(eventsQueue, &event);

        if (userWantToExit(event))
            return Item::EXIT;

        if (itemPicked(event))
            return items_[currentItem].second;

        if (escapePicked(event))
            return items_[items_.size() - 1].second;

        currentItem = getCurrentItem(event, currentItem);

        if (event.type == ALLEGRO_EVENT_TIMER)
            shouldRedraw = true;

        if (shouldRedraw && al_is_event_queue_empty(eventsQueue))
        {
            shouldRedraw = false;
            redraw(currentItem);
        }
    }
}
