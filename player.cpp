#include "player.h"
#include "config.h"
#include "vehicle.h"

Player::Player() : font_{al_create_builtin_font()}
{
    setTanks(0);
    buffer_ = al_create_bitmap(200, MAP_SIZE * E_SIZE);
}

Player::~Player()
{
    al_destroy_bitmap(buffer_);
    al_destroy_font(font_);
}

void Player::loadVehicle(Vehicle* v)
{
    setVehicle(v);
    x_ = v->getX();
    y_ = v->getY();
    setLevel(v->getType());
}

ALLEGRO_BITMAP* Player::display()
{
    al_set_target_bitmap(buffer_);
    al_clear_to_color(al_map_rgb(0, 0, 255));
    al_draw_text(font_, al_map_rgb(255, 255, 255),
                 al_get_bitmap_width(buffer_) / 2,
                 al_get_bitmap_height(buffer_) / 2, ALLEGRO_ALIGN_CENTER,
                 "[Status placeholder]");
    return buffer_;
}

void Player::setTanks(int tanks) { ptanks_ = tanks; }

int Player::getLevel()
{
    try
    {
        return getVehicle()->getType();
    }
    catch (...)
    {
        return plevel_;
    }
}

void Player::setLevel(int level) { plevel_ = level; }

int Player::getTanks() { return ptanks_; }

Vehicle* Player::getVehicle()
{
    if (vehicle_ != NULL)
    {
        return vehicle_;
    }
    if (getTanks() > 0)
    {
        setVehicle(new Vehicle(getLevel(), x_, y_));
        setTanks(getTanks() - 1);
        return vehicle_;
    }
    throw Lose();
}

void Player::setVehicle(Vehicle* v) { vehicle_ = v; }

Vehicle* Player::killVehicle()
{
    // delete vehicle_;
    vehicle_ = nullptr;
    return getVehicle();
}

void Lose::display()
{
    al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    al_clear_to_color(al_map_rgb(0, 0, 255));
    ALLEGRO_FONT* font{al_create_builtin_font()};
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2,
                 ALLEGRO_ALIGN_CENTER, "You loose");
    al_destroy_font(font);
    al_flip_display();
    al_rest(2);
}

void Win::display()
{
    al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    al_clear_to_color(al_map_rgb(0, 0, 255));
    ALLEGRO_FONT* font{al_create_builtin_font()};
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2,
                 ALLEGRO_ALIGN_CENTER, "You Win");
    al_destroy_font(font);
    al_flip_display();
    al_rest(2);
}
