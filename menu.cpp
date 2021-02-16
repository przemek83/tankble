#include "menu.h"
#include "config.h"
#include "game.h"

// constructor

// Item::Item(int (Game::*pointer)(), const char* t, bool b)
//{
//    func = pointer;
//    text = t;
//    back = b;
//}

// destructor

// Item::~Item() {}

// constructor

Menu::Menu(int ws, int hs, int iw, int ih) : font(al_create_builtin_font())
{
    widthScreen = ws;
    heightScreen = hs;
    itemWidth = iw;
    itemHeight = ih;
    // PALETTE palette;
    itemBg = al_load_bitmap("image/menu_item2.tga");               //, palette);
    itemBgSelect = al_load_bitmap("image/menu_item_select2.tga");  //, palette);
    menuBg = al_load_bitmap("image/background.tga");
    subMenuBg = al_load_bitmap("image/background_menu2.tga");
    yTopItem = 0;
    check = 0;  // pozycja z menu
    this->bmp = al_create_bitmap(itemWidth, itemHeight);
}

// destructor

Menu::~Menu()
{
    // poniewaz kontener vector nie obsluguje destrukcji wskaznikow
    // musimy to zrobic sami...
    //    for (uint i = 0; i < items_.size(); i++)
    //        delete items[i];
    al_destroy_bitmap(itemBg);
    al_destroy_bitmap(itemBgSelect);
    al_destroy_bitmap(subMenuBg);
    al_destroy_bitmap(menuBg);
}

// add position to menu

Menu::Item Menu::getUserChoice(std::vector<std::pair<string, Item> > items)
{
    items_ = std::move(items);
    // items.push_back(pointer);
    // wysoksc pierwszej pozycji w menu
    yTopItem = heightScreen / 2 - items_.size() * itemHeight / 2;
    return loop();
}

void Menu::drawMenuItems(unsigned int currentItem)
{
    for (unsigned int i = 0; i < items_.size(); i++)
    {
        ALLEGRO_BITMAP* itemBitmap{nullptr};
        if (i == currentItem)
            itemBitmap = itemBgSelect;
        else
            itemBitmap = itemBg;
        al_draw_bitmap_region(itemBitmap, 0, 0, itemWidth, itemHeight,
                              widthScreen / 2 - itemWidth / 2,
                              yTopItem + itemHeight * i, 0);
        al_draw_text(font, al_map_rgb(255, 255, 255), widthScreen / 2,
                     yTopItem + itemHeight * i + itemHeight / 2,
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
            if ((event.mouse.x > widthScreen / 2 - itemWidth / 2) &&
                (event.mouse.x < widthScreen / 2 + itemWidth / 2) &&
                (event.mouse.y > yTopItem + itemHeight * (int)i) &&
                (event.mouse.y < yTopItem + itemHeight + itemHeight * (int)i))
                return i;
        }
    }

    return currentItem;
}

bool Menu::userWantToExit(const ALLEGRO_EVENT& event) const
{
    return event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ||
           (event.type == ALLEGRO_EVENT_KEY_UP &&
            event.keyboard.keycode == ALLEGRO_KEY_ESCAPE);
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
    al_draw_bitmap(menuBg, 0, 0, 0);
    drawMenuItems(currentItem);
    al_flip_display();
}

Menu::Item Menu::loop()
{
    //    if (items_.empty())
    //        return 1;

    ALLEGRO_EVENT_QUEUE* events{al_create_event_queue()};
    ALLEGRO_TIMER* timer{al_create_timer(1.0 / 30)};
    al_register_event_source(events, al_get_keyboard_event_source());
    al_register_event_source(events, al_get_mouse_event_source());
    al_register_event_source(
        events, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(events, al_get_timer_event_source(timer));
    al_start_timer(timer);

    bool shouldRedraw{true};

    al_show_mouse_cursor(al_get_current_display());

    unsigned int currentItem{0};

    while (true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(events, &event);  // Wait for and get an event.

        if (userWantToExit(event))
            return Item::EXIT;

        if (itemPicked(event))
        {
            std::cout << "Clicked " << currentItem << std::endl;
            return items_[currentItem].second;
            //(g->*(items[(uint)selectedItem]->func))();
        }

        currentItem = getCurrentItem(event, currentItem);

        if (event.type == ALLEGRO_EVENT_TIMER)
            shouldRedraw = true;

        if (shouldRedraw && al_is_event_queue_empty(events))
        {
            shouldRedraw = false;
            redraw(currentItem);
        }
    }
    al_hide_mouse_cursor(al_get_current_display());

    return Item::BACK;
}

// end of menu.cpp
