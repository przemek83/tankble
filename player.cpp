#include "player.h"
#include "config.h"
#include "vehicle.h"

Player::Player()
{
    this->source = "image/player_background.tga";
    if (!loadBitmap())
    {
        exit(0);
    }
    this->setTanks(0);
    this->buffer = al_create_bitmap(200, MAP_SIZE * E_SIZE);
}

Player::~Player()
{
    al_destroy_bitmap(this->bmp);
    al_destroy_bitmap(this->buffer);
}

void Player::loadVehicle(Vehicle* v)
{
    this->setVehicle(v);
    this->x = v->getX();
    this->y = v->getY();
    this->setLevel(v->getType());
}

bool Player::loadBitmap()
{
    // PALETTE palette;
    FILE* fp;
    if ((fp = fopen(source, "r")) == NULL)
    {
        return false;
    }
    fclose(fp);
    this->bmp = al_load_bitmap(this->source);  //, palette);
    return true;
}

ALLEGRO_BITMAP* Player::display()
{
    al_set_target_bitmap(buffer);
    al_draw_bitmap_region(this->bmp, 0, 0, 200, MAP_SIZE * E_SIZE, 0, 0, 0);
    /*tutaj reszta do wyswietlen*/
    return this->buffer;
}

void Player::setTanks(int tanks) { this->ptanks = tanks; }

int Player::getArmor() { return this->getVehicle()->getArmor(); }

int Player::getSpeed() { return this->getVehicle()->getSpeed(); }

int Player::getLevel()
{
    try
    {
        return this->getVehicle()->getType();
    }
    catch (...)
    {
        return this->plevel;
    }
}

void Player::setLevel(int level) { this->plevel = level; }

int Player::getTanks() { return this->ptanks; }

int Player::getPower() { return this->getVehicle()->getPower(); }

Vehicle* Player::getVehicle()
{
    if (this->vehicle != NULL)
    {
        return this->vehicle;
    }
    if (this->getTanks() > 0)
    {
        this->setVehicle(new Vehicle(this->getLevel(), this->x, this->y));
        this->setTanks(this->getTanks() - 1);
        return this->vehicle;
    }
    throw Lose();
}

void Player::setVehicle(Vehicle* v) { this->vehicle = v; }

Vehicle* Player::killVehicle()
{
    // delete this->vehicle;
    this->vehicle = NULL;
    return this->getVehicle();
}
ALLEGRO_BITMAP* Player::getVehicleBitmap()
{
    return this->getVehicle()->display();
}

void Lose::display()
{
    this->source = "image/lose.tga";
    if (!loadBitmap())
    {
        exit(0);
    }
    al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    al_draw_bitmap(bmp, 0, 0, 0);
    al_flip_display();
    // clear_keybuf();
    al_rest(2);
    //    while (!keypressed())
    //        ;
}

bool Lose::loadBitmap()
{
    // PALETTE palette;
    FILE* fp;
    if ((fp = fopen(source, "r")) == NULL)
    {
        return false;
    }
    fclose(fp);
    this->bmp = al_load_bitmap(this->source);  //, palette);
    return true;
}

void Win::display()
{
    this->source = "image/win.tga";
    if (!loadBitmap())
    {
        exit(0);
    }
    al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    al_draw_bitmap(bmp, 0, 0, 0);
    al_flip_display();
    // clear_keybuf();
    al_rest(2);
    //    while (!keypressed())
    //        ;
}
