#include "menu.h"
#include "config.h"
#include "game.h"

Menu::Menu(unsigned int width, unsigned int height)
    : menuBg_{al_load_bitmap("image/menu/background.bmp")},
      itemBg_{al_load_bitmap("image/menu/item.tga")},
      itemBgSelect_{al_load_bitmap("image/menu/item_select.tga")},
      font_{al_create_builtin_font()},
      width_{width},
      height_{height}
{
    items_ = getMainMenu();
}

Menu::~Menu()
{
    al_destroy_bitmap(itemBg_);
    al_destroy_bitmap(itemBgSelect_);
    al_destroy_bitmap(menuBg_);
    al_destroy_font(font_);
}

void Menu::setMenuSize(unsigned int width, unsigned int height)
{
    width_ = width;
    height_ = height;
}

std::vector<std::pair<std::string, Menu::UserChoice>> Menu::getMainMenu() const
{
    return {{"NEW GAME", UserChoice::NEW_MENU},
            {"OPTIONS", UserChoice::OPTIONS_MENU},
            {"EXIT", UserChoice::EXIT}};
}

std::vector<std::pair<std::string, Menu::UserChoice>> Menu::getNewGameMenu()
    const
{
    return {{"1 PLAYER", UserChoice::NEW_1P}, {"BACK", UserChoice::BACK}};
}

std::vector<std::pair<std::string, Menu::UserChoice>> Menu::getOptionsMenu()
    const
{
    return {{"FULL SCREEN", UserChoice::FULLSCREEN},
            {"WINDOWED", UserChoice::WINDOWED},
            {"BACK", UserChoice::BACK}};
}

Menu::Item Menu::getItem()
{
    al_show_mouse_cursor(al_get_current_display());

    Item pickedItem{Item::NO_ITEM};
    while (pickedItem == Item::NO_ITEM)
    {
        switch (getUserChoice())
        {
            case UserChoice::MAIN_MENU:
            case UserChoice::BACK:
                items_ = getMainMenu();
                break;

            case UserChoice::NEW_MENU:
                items_ = getNewGameMenu();
                break;

            case UserChoice::OPTIONS_MENU:
                items_ = getOptionsMenu();
                break;

            case UserChoice::WINDOWED:
                pickedItem = Item::WINDOWED;
                break;

            case UserChoice::FULLSCREEN:
                pickedItem = Item::FULLSCREEN;
                break;

            case UserChoice::EXIT:
                pickedItem = Item::EXIT;
                break;

            case UserChoice::NEW_1P:
                pickedItem = Item::NEW_1P;
                break;
        }
    }

    al_hide_mouse_cursor(al_get_current_display());
    return pickedItem;
}

Menu::UserChoice Menu::getUserChoice()
{
    auto [eventsQueue, timer]{sutupEventQueueAndTimer()};
    bool shouldRedraw{true};
    for (unsigned int currentItem{0};;)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(eventsQueue, &event);

        if (userWantToExit(event))
            return UserChoice::EXIT;

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

void Menu::drawMenuItems(unsigned int currentItem)
{
    const unsigned int firstItem{getLocationOfFirstItem()};
    const float itemWidth{static_cast<float>(getItemWidth())};
    const float itemHeight{static_cast<float>(getItemHeight())};
    const float itemMiddleY{itemHeight / 2.F};
    const float screenMiddleX{static_cast<float>(width_) / 2.F};
    const float itemX{screenMiddleX - itemWidth / 2.F};
    const ALLEGRO_COLOR white{al_map_rgb(255, 255, 255)};

    for (unsigned int i = 0; i < items_.size(); i++)
    {
        ALLEGRO_BITMAP* itemBitmap{nullptr};
        if (i == currentItem)
            itemBitmap = itemBgSelect_;
        else
            itemBitmap = itemBg_;

        const float itemY{static_cast<float>(firstItem) +
                          itemHeight * static_cast<float>(i)};
        al_draw_bitmap_region(itemBitmap, 0., 0., itemWidth, itemHeight, itemX,
                              itemY, 0);
        al_draw_text(font_, white, screenMiddleX, itemY + itemMiddleY,
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
        const unsigned int firstItem{getLocationOfFirstItem()};
        const unsigned int mouseX{static_cast<unsigned int>(event.mouse.x)};
        const unsigned int mouseY{static_cast<unsigned int>(event.mouse.y)};
        const unsigned int itemWidth{getItemWidth()};
        const unsigned int itemHeight{getItemHeight()};
        for (unsigned int i = 0; i < items_.size(); i++)
        {
            if ((mouseX > width_ / 2 - itemWidth / 2) &&
                (mouseX < width_ / 2 + itemWidth / 2) &&
                (mouseY > firstItem + itemHeight * i) &&
                (mouseY < firstItem + itemHeight + itemHeight * i))
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
    al_clear_to_color(al_map_rgb_f(0., 0., 0.));
    al_draw_scaled_bitmap(
        menuBg_, 0., 0., static_cast<float>(al_get_bitmap_width(menuBg_)),
        static_cast<float>(al_get_bitmap_height(menuBg_)), 0., 0.,
        static_cast<float>(width_), static_cast<float>(height_), 0);
    drawMenuItems(currentItem);
    al_flip_display();
}

bool Menu::escapePicked(const ALLEGRO_EVENT& event) const
{
    return event.type == ALLEGRO_EVENT_KEY_UP &&
           event.keyboard.keycode == ALLEGRO_KEY_ESCAPE;
}

unsigned int Menu::getLocationOfFirstItem() const
{
    return height_ / 2 -
           static_cast<unsigned int>(items_.size()) * getItemHeight() / 2;
}

unsigned int Menu::getItemWidth() const
{
    return static_cast<unsigned int>(al_get_bitmap_width(itemBg_));
}

unsigned int Menu::getItemHeight() const
{
    return static_cast<unsigned int>(al_get_bitmap_height(itemBg_));
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
