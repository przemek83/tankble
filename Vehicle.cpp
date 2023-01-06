#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <iostream>

#include "Config.h"
#include "Map.h"
#include "Vehicle.h"
#include "map/Bullet.h"

const int Vehicle::wayX_[4] = {0, 1, 0, -1};
const int Vehicle::wayY_[4] = {-1, 0, 1, 0};
const int Vehicle::powers_[8] = {2, 4, 8, 16, 1, 2, 4, 8};
const int Vehicle::armors_[8] = {8, 16, 32, 64, 4, 8, 16, 32};
const int Vehicle::speeds_[8] = {4, 4, 6, 8, 4, 4, 6, 8};
const int Vehicle::ids_[8] = {101, 102, 103, 104, 201, 202, 203, 204};
const int Vehicle::directions_[8] = {0, 0, 0, 0, 2, 2, 2, 2};

Vehicle::Vehicle(int tankType, unsigned int x, unsigned int y) : x_(x), y_(y)
{
    direction_ = directions_[tankType];
    setType(tankType);

    if (!loadBitmaps(tankType))
        exit(0);
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
    if (!std::filesystem::exists(tankTypesPaths_[tankType].c_str()))
        return false;

    bmp_[0] = al_load_bitmap(tankTypesPaths_[tankType].c_str());
    const int width{al_get_bitmap_width(bmp_[0])};
    const int height{al_get_bitmap_height(bmp_[0])};

    bmp_[1] = al_create_bitmap(width, height);
    al_set_target_bitmap(bmp_[1]);
    al_draw_rotated_bitmap(bmp_[0], width / 2, height / 2, width / 2,
                           height / 2, pi() / 2, 0);
    bmp_[2] = al_create_bitmap(al_get_bitmap_width(bmp_[0]),
                               al_get_bitmap_height(bmp_[0]));
    al_set_target_bitmap(bmp_[2]);
    al_draw_rotated_bitmap(bmp_[0], width / 2, height / 2, width / 2,
                           height / 2, pi(), 0);
    bmp_[3] = al_create_bitmap(al_get_bitmap_width(bmp_[0]),
                               al_get_bitmap_height(bmp_[0]));
    al_set_target_bitmap(bmp_[3]);
    al_draw_rotated_bitmap(bmp_[0], width / 2, height / 2, width / 2,
                           height / 2, 3 * pi() / 2, 0);

    return true;
}

int Vehicle::getId() const { return id_; }

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

void Vehicle::fire(Map& map)
{
    time_t ti = time(nullptr);
    if (difftime(ti, lastFire_) > 1.0)
    {
        lastFire_ = ti;
        map.addBullet(std::make_unique<Bullet>(this));
    }
}

bool Vehicle::destroy(int power)
{
    armor_ -= power;
    if (armor_ <= 0)
        return true;
    return false;
}

int Vehicle::getMaxArmor() const { return maxArmor_; }

int Vehicle::getType() const
{
    return (getId() % 100) - 1;
    /*0-3*/
}

int Vehicle::getX() const { return x_; }
int Vehicle::getY() const { return y_; }
void Vehicle::setX(int x) { x_ = x; }
void Vehicle::setY(int y) { y_ = y; }

void Vehicle::setMaxArmor() { armor_ = getMaxArmor(); }

void Vehicle::setSpeedUp() { speed_++; }

int Vehicle::getPower() const { return power_; }

int Vehicle::getSpeed() const { return speed_; }

int Vehicle::getDirection() const { return direction_; }

int Vehicle::getDirectionX() const { return wayX_[getDirection()]; }

int Vehicle::getDirectionY() const { return wayY_[getDirection()]; }

void Vehicle::resetFire() { lastFire_--; }

void Vehicle::go()
{
    setX(getX() + getDirectionX() + getDirectionX());
    setY(getY() + getDirectionY() + getDirectionY());
}

void Vehicle::moveRandom(Map& map)
{
    if (getX() % Config::elementSize == 0 && getY() % Config::elementSize == 0)
    {
        const int i{rand() % 8};
        if (i < 4)
        {
            direction_ = i;
        }
        if (!(map.isValid(getX() + getDirectionX() + getDirectionX(),
                          getY() + getDirectionY() + getDirectionY())))
        {
            return;
        }
        if (!map.canDrive(getX() / Config::elementSize + getDirectionX(),
                          getY() / Config::elementSize + getDirectionY()))
        {
            return;
        }
    }
    go();
}

constexpr double Vehicle::pi() const { return std::atan(1) * 4; }
