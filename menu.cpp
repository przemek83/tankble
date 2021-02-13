#include "menu.h"
#include "config.h"
#include "game.h"

// constructor

Item::Item(int (Game::*pointer)(), const char* t, bool b)
{
    func = pointer;
    text = t;
    back = b;
}

// destructor

Item::~Item() {}

// constructor

Menu::Menu(int ws, int hs, int iw, int ih)
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
    for (uint i = 0; i < items.size(); i++)
        delete items[i];
    al_destroy_bitmap(itemBg);
    al_destroy_bitmap(itemBgSelect);
    al_destroy_bitmap(subMenuBg);
    al_destroy_bitmap(menuBg);
}

// add position to menu

void Menu::addItem(Item* pointer)
{
    items.push_back(pointer);
    // wysoksc pierwszej pozycji w menu
    yTopItem = heightScreen / 2 - items.size() * itemHeight / 2;
}

// draw whole menu

void Menu::draw(ALLEGRO_BITMAP* buffer)
{
    int countx = 0;
    ALLEGRO_KEYBOARD_STATE key_state;
    al_get_keyboard_state(&key_state);
    //    if (keypressed())
    //    {
    if ((al_key_down(&key_state, ALLEGRO_KEY_UP) ||
         al_key_down(&key_state, ALLEGRO_KEY_DOWN)) &&
        check == -1)
    {
        check = 0;  // na start
        al_set_mouse_xy(nullptr, widthScreen / 2 + itemWidth / 3,
                        yTopItem + itemHeight * check + itemHeight / 2);
    }
    else if (al_key_down(&key_state, ALLEGRO_KEY_UP) && check >= 0)
    {
        check = (check - 1 + items.size()) % items.size();
        al_set_mouse_xy(nullptr, widthScreen / 2 + itemWidth / 3,
                        yTopItem + itemHeight * check + itemHeight / 2);
    }
    else if (al_key_down(&key_state, ALLEGRO_KEY_DOWN) && check >= 0)
    {
        check = (check + 1) % items.size();
        al_set_mouse_xy(nullptr, widthScreen / 2 + itemWidth / 3,
                        yTopItem + itemHeight * check + itemHeight / 2);
    }
    // clear_keybuf();
    //}
    for (uint i = 0; i < items.size(); i++)
    {
        ALLEGRO_MOUSE_STATE mouse_state;
        al_get_mouse_state(&mouse_state);

        /* Copy it to the bmp. */
        if ((mouse_state.x > widthScreen / 2 - itemWidth / 2) &&
            (mouse_state.x < widthScreen / 2 + itemWidth / 2) &&
            (mouse_state.y > yTopItem + itemHeight * (int)i) &&
            (mouse_state.y < yTopItem + itemHeight + itemHeight * (int)i))
        {
            al_set_target_bitmap(buffer);
            al_draw_bitmap_region(itemBgSelect, 0, 0, 0, 0, itemWidth,
                                  itemHeight, 0);
            check = (int)i;
        }
        else
        {
            al_set_target_bitmap(buffer);
            al_draw_bitmap_region(itemBg, 0, 0, 0, 0, itemWidth, itemHeight, 0);
            // blit(itemBg, bmp, 0, 0, 0, 0, itemWidth, itemHeight);
            countx++;
        }
        // print text to itemBg with white color to (-1) = transparent
        // background item -> 340x70

        al_set_target_bitmap(buffer);
        //        textout_centre_ex(bmp, font, items[i]->text, itemWidth / 2,
        //                          itemHeight / 2, makecol(255, 255, 255), -1);
        al_draw_bitmap_region(bmp, 0, 0, widthScreen / 2 - itemWidth / 2,
                              yTopItem + itemHeight * i, itemWidth, itemHeight,
                              0);
    }
    if (countx == items.size())
    {
        check = -1;  // jesli myszka wyszla poza menu
    }
    // for debug
    // cout << "count: " << countx << " " << check << "\n";
}

// loop

int Menu::loop(ALLEGRO_BITMAP* buffer, Game* g)
{
    bool end = false;
    bool tmp = false;  // zmienna pomocnicza
    if (items.size() == 0)
        return 1;

    ALLEGRO_MOUSE_STATE mouse_state;
    ALLEGRO_KEYBOARD_STATE key_state;
    ALLEGRO_EVENT_QUEUE* events;

    events = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30);
    al_register_event_source(events, al_get_keyboard_event_source());
    al_register_event_source(
        events, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(events, al_get_timer_event_source(timer));
    al_start_timer(timer);

    bool redraw = false;

    // bitmap = al_load_bitmap

    while (1)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(events, &event);  // Wait for and get an event.

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;

        if (event.type == ALLEGRO_EVENT_KEY_DOWN &&
            event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            return 0;

        // Redraw, but only if the event queue is empty
        if (redraw && al_is_event_queue_empty(events))
        {
            redraw = false;
            // Clear so we don't get trippy artifacts left after zoom.
            al_clear_to_color(al_map_rgb_f(0, 0, 0));
            al_draw_bitmap(menuBg, 0, 0, 0);
            // draw(buffer);
            al_flip_display();
        }
    }

    do
    {
        // clear_to_color( buffer, makecol(0,0,0) ); // czysci ekran
        // clear_bitmap( buffer );
        al_set_target_bitmap(buffer);
        al_draw_bitmap_region(menuBg, 0, 0, 0, 0, widthScreen, heightScreen, 0);
        //        blit(menuBg, buffer, 0, 0, 0, 0, widthScreen, heightScreen);
        // set_trans_blender(0, 0, 0, 128);
        // drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
        // masked_blit( subMenuBg, buffer, 0, 0, widthScreen/2-220,
        // heightScreen/2-200, 440, 400 );
        //        draw_trans_sprite(buffer, subMenuBg, widthScreen / 2 - 220,
        //                          heightScreen / 2 - 200);
        //        drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);

        al_get_mouse_state(&mouse_state);
        al_get_keyboard_state(&key_state);

        // poll_mouse();  // sprawdza pozycje myszki
        draw(buffer);  // rysuje przyciski menu
        if (!(mouse_state.buttons & 1) &&
            !al_key_down(&key_state, ALLEGRO_KEY_ENTER))
            tmp = true;
        else if (((mouse_state.buttons & 1) ||
                  al_key_down(&key_state, ALLEGRO_KEY_ENTER)) &&
                 tmp)
        {
            // check pochodzi z funkcji draw, ktora zwrocila nr podswietlonej
            // pozycji
            if (check >= 0)
            {
                // wywolanie funkcji przez referencje dana w funkcji addItem
                (g->*(items[(uint)check]->func))();
                tmp = false;
                // wyjscie z tego menu (back)
                if (items[(uint)check]->back)
                    end = true;
                // jesli wiemy juz ktora pozycje uzytkownik wybral
                // to nie ma sensu kontynuowanie petli...
            }
            // cout << "Wybor: " << check << "\n";
        }  // else if()
        // pokazuje kursor myszy
        // al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
        al_show_mouse_cursor(al_get_current_display());
        // show_mouse(buffer);
        // likwiduje efekt mrugania ekranu
        // blit obsluguje przezroczystosc, draw_sprite nie
        al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
        al_draw_bitmap_region(buffer, 0, 0, 0, 0, widthScreen, heightScreen, 0);
        al_hide_mouse_cursor(al_get_current_display());
    } while (!end);
    return 0;
}

// end of menu.cpp
