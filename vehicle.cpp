#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "config.h"
#include "map.h"
#include "vehicle.h"

const int Vehicle::wayX_[4] = {0, 1, 0, -1};
const int Vehicle::wayY_[4] = {-1, 0, 1, 0};
const int Vehicle::powers_[8] = {2, 4, 8, 16, 1, 2, 4, 8};
const int Vehicle::armors_[8] = {8, 16, 32, 64, 4, 8, 16, 32};
const int Vehicle::speeds_[8] = {4, 4, 6, 8, 4, 4, 6, 8};
const int Vehicle::ids_[8] = {101, 102, 103, 104, 201, 202, 203, 204};
const int Vehicle::directions_[8] = {0, 0, 0, 0, 2, 2, 2, 2};

Vehicle::Vehicle(int tankType, unsigned int x, unsigned int y)
{
    fly_ = 0;
    drive_ = 1;

    setX(x);
    setY(y);

    direction_ = directions_[tankType];
    setType(tankType);

    if (!loadBitmaps(tankType))
    {
        exit(0);
    }

    lastFire_ = 0;
}

Vehicle::~Vehicle()
{
    al_destroy_bitmap(bmp_[0]);
    al_destroy_bitmap(bmp_[1]);
    al_destroy_bitmap(bmp_[2]);
    al_destroy_bitmap(bmp_[3]);
    std::cout << "Vehicle:" << getId() << " is deleted\n";
}

bool Vehicle::loadBitmaps(int tankType)
{
    FILE* fp;
    if ((fp = fopen(tankTypesPaths_[tankType].c_str(), "r")) == NULL)
        return false;
    fclose(fp);

    bmp_[0] = al_load_bitmap(tankTypesPaths_[tankType].c_str());
    const int width{al_get_bitmap_width(bmp_[0])};
    const int height{al_get_bitmap_height(bmp_[0])};

    bmp_[1] = al_create_bitmap(width, height);
    al_set_target_bitmap(bmp_[1]);
    al_draw_rotated_bitmap(bmp_[0], width / 2, height / 2, width / 2,
                           height / 2, M_PI / 2, 0);
    bmp_[2] = al_create_bitmap(al_get_bitmap_width(bmp_[0]),
                               al_get_bitmap_height(bmp_[0]));
    al_set_target_bitmap(bmp_[2]);
    al_draw_rotated_bitmap(bmp_[0], width / 2, height / 2, width / 2,
                           height / 2, M_PI, 0);
    bmp_[3] = al_create_bitmap(al_get_bitmap_width(bmp_[0]),
                               al_get_bitmap_height(bmp_[0]));
    al_set_target_bitmap(bmp_[3]);
    al_draw_rotated_bitmap(bmp_[0], width / 2, height / 2, width / 2,
                           height / 2, 3 * M_PI / 2, 0);

    return true;
}

int Vehicle::getId() { return id_; }

void Vehicle::setType(int tankType)
{
    if (tankType < 0 || tankType > 7)
    {
        tankType = 0;
    }
    id_ = ids_[tankType];
    armor_ = armors_[tankType];
    maxArmor_ = armors_[tankType];
    power_ = powers_[tankType];
    speed_ = speeds_[tankType];

    if (!loadBitmaps(tankType))
    {
        exit(1);
    }
}

void Vehicle::move(int xy) { direction_ = xy; }

ALLEGRO_BITMAP* Vehicle::display() { return bmp_[getDirection()]; }

void Vehicle::fire(void* map)
{
    Map* mapa = (Map*)map;
    time_t ti = time(NULL);
    if (difftime(ti, lastFire_) > 1.0)
    {
        lastFire_ = ti;
        Bullet* bullet = new Bullet(this);
        mapa->addBullet(bullet);
    }
}

bool Vehicle::destroy(int power)
{
    armor_ -= power;
    if (armor_ <= 0)
        return true;
    return false;
}

int Vehicle::getMaxArmor() { return maxArmor_; }

int Vehicle::getType()
{
    return (getId() % 100) - 1;
    /*0-3*/
}

int Vehicle::getX() { return x_; }
int Vehicle::getY() { return y_; }
void Vehicle::setX(int x) { x_ = x; }
void Vehicle::setY(int y) { y_ = y; }
int Vehicle::getArmor() { return armor_; }
void Vehicle::setArmor(int armor) { armor_ = armor; }

void Vehicle::setMaxArmor() { armor_ = getMaxArmor(); }

bool Vehicle::canFly() { return fly_; }

bool Vehicle::canDrive() { return drive_; }

void Vehicle::setSpeedUp() { speed_++; }

int Vehicle::getPower() { return power_; }

int Vehicle::getSpeed() { return speed_; }

int Vehicle::getDirection() { return direction_; }

int Vehicle::getDirectionX() { return wayX_[getDirection()]; }

int Vehicle::getDirectionY() { return wayY_[getDirection()]; }

void Vehicle::resetFire() { lastFire_--; }

void Vehicle::go()
{
    setX(getX() + getDirectionX() + getDirectionX());
    setY(getY() + getDirectionY() + getDirectionY());
}

void Vehicle::moveRandom(void* map)
{
    int i;
    Map* mapa = (Map*)map;
    if (getX() % Config::elementSize == 0 && getY() % Config::elementSize == 0)
    {
        i = rand() % 8;
        if (i < 4)
        {
            direction_ = i;
        }
        if (!(mapa->isValid(getX() + getDirectionX() + getDirectionX(),
                            getY() + getDirectionY() + getDirectionY())))
        {
            return;
        }
        if (!mapa->canDrive(getX() / Config::elementSize + getDirectionX(),
                            getY() / Config::elementSize + getDirectionY()))
        {
            return;
        }
    }
    go();
}
