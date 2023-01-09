#include "Tank.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <iostream>

#include <allegro5/allegro.h>

#include "Config.h"
#include "Map.h"
#include "TankType.h"
#include "map/Bullet.h"

const int Tank::wayX_[4] = {0, 1, 0, -1};
const int Tank::wayY_[4] = {-1, 0, 1, 0};
const int Tank::powers_[8] = {2, 4, 8, 16, 1, 2, 4, 8};
const int Tank::armors_[8] = {8, 16, 32, 64, 4, 8, 16, 32};
const int Tank::speeds_[8] = {4, 4, 6, 8, 4, 4, 6, 8};
const int Tank::directions_[8] = {0, 0, 0, 0, 2, 2, 2, 2};

Tank::Tank(TankType tankType, unsigned int x, unsigned int y)
    : x_(x), y_(y), initialX_(x), initialY_(y)
{
    direction_ = directions_[static_cast<int>(tankType)];
    setType(tankType);

    if (isPlayerControlled())
        lives_ *= 2;

    if (!loadBitmaps(tankType))
        exit(0);
}

Tank::~Tank()
{
    al_destroy_bitmap(bmp_[0]);
    al_destroy_bitmap(bmp_[1]);
    al_destroy_bitmap(bmp_[2]);
    al_destroy_bitmap(bmp_[3]);
    std::cout << "Vehicle:" << static_cast<int>(getTankType())
              << " is deleted\n";
}

bool Tank::loadBitmaps(TankType tankType)
{
    if (!std::filesystem::exists(
            tankTypesPaths_[static_cast<int>(tankType)].c_str()))
        return false;

    bmp_[0] =
        al_load_bitmap(tankTypesPaths_[static_cast<int>(tankType)].c_str());
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

void Tank::setType(TankType tankType)
{
    type_ = tankType;
    armor_ = armors_[static_cast<int>(tankType)];
    maxArmor_ = armors_[static_cast<int>(tankType)];
    power_ = powers_[static_cast<int>(tankType)];
    speed_ = speeds_[static_cast<int>(tankType)];

    if (!loadBitmaps(tankType))
    {
        exit(1);
    }
}

void Tank::move(int xy) { direction_ = xy; }

ALLEGRO_BITMAP* Tank::display() { return bmp_[getDirection()]; }

void Tank::fire(Map& map)
{
    time_t ti = time(nullptr);
    if (difftime(ti, lastFire_) > 1.0)
    {
        lastFire_ = ti;
        map.addBullet(std::make_unique<Bullet>(this));
    }
}

bool Tank::destroy(int power)
{
    armor_ -= power;
    if (armor_ <= 0)
    {
        if (lives_ <= 1)
            return true;
        lives_--;
        resetState();
    }
    return false;
}

int Tank::getMaxArmor() const { return maxArmor_; }

TankType Tank::getTankType() const { return type_; }

int Tank::getX() const { return x_; }
int Tank::getY() const { return y_; }
void Tank::setX(int x) { x_ = x; }
void Tank::setY(int y) { y_ = y; }

void Tank::setMaxArmor() { armor_ = getMaxArmor(); }

void Tank::setSpeedUp() { speed_++; }

int Tank::getPower() const { return power_; }

int Tank::getSpeed() const { return speed_; }

int Tank::getDirection() const { return direction_; }

int Tank::getDirectionX() const { return wayX_[getDirection()]; }

int Tank::getDirectionY() const { return wayY_[getDirection()]; }

bool Tank::isPlayerControlled() const
{
    return type_ == TankType::PLAYER_TIER_1 ||
           type_ == TankType::PLAYER_TIER_2 ||
           type_ == TankType::PLAYER_TIER_3 || type_ == TankType::PLAYER_TIER_4;
}

void Tank::addLife() { lives_++; }

void Tank::resetFire() { lastFire_--; }

void Tank::go()
{
    setX(getX() + getDirectionX() + getDirectionX());
    setY(getY() + getDirectionY() + getDirectionY());
}

void Tank::moveRandom(Map& map)
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

constexpr double Tank::pi() const { return std::atan(1) * 4; }

void Tank::resetState()
{
    setX(initialX_);
    setY(initialY_);
    if (isPlayerControlled())
        setType(TankType::PLAYER_TIER_1);
}