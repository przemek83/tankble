#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <iostream>

#include "Config.h"
#include "Map.h"
#include "TankType.h"
#include "Vehicle.h"
#include "map/Bullet.h"

const int Vehicle::wayX_[4] = {0, 1, 0, -1};
const int Vehicle::wayY_[4] = {-1, 0, 1, 0};
const int Vehicle::powers_[8] = {2, 4, 8, 16, 1, 2, 4, 8};
const int Vehicle::armors_[8] = {8, 16, 32, 64, 4, 8, 16, 32};
const int Vehicle::speeds_[8] = {4, 4, 6, 8, 4, 4, 6, 8};
const int Vehicle::directions_[8] = {0, 0, 0, 0, 2, 2, 2, 2};

Vehicle::Vehicle(TankType tankType, unsigned int x, unsigned int y)
    : x_(x), y_(y), initialX_(x), initialY_(y)
{
    direction_ = directions_[static_cast<int>(tankType)];
    setType(tankType);

    if (isPlayerControlled())
        lives_ *= 2;

    if (!loadBitmaps(tankType))
        exit(0);
}

Vehicle::~Vehicle()
{
    al_destroy_bitmap(bmp_[0]);
    al_destroy_bitmap(bmp_[1]);
    al_destroy_bitmap(bmp_[2]);
    al_destroy_bitmap(bmp_[3]);
    std::cout << "Vehicle:" << static_cast<int>(getTankType())
              << " is deleted\n";
}

bool Vehicle::loadBitmaps(TankType tankType)
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

void Vehicle::setType(TankType tankType)
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
    {
        if (lives_ <= 1)
            return true;
        lives_--;
        resetState();
    }
    return false;
}

int Vehicle::getMaxArmor() const { return maxArmor_; }

TankType Vehicle::getTankType() const { return type_; }

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

bool Vehicle::isPlayerControlled() const
{
    return type_ == TankType::PLAYER_TIER_1 ||
           type_ == TankType::PLAYER_TIER_2 ||
           type_ == TankType::PLAYER_TIER_3 || type_ == TankType::PLAYER_TIER_4;
}

void Vehicle::addLife() { lives_++; }

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

void Vehicle::resetState()
{
    setX(initialX_);
    setY(initialY_);
    if (isPlayerControlled())
        setType(TankType::PLAYER_TIER_1);
}
