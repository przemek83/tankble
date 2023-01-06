#include "Bullet.h"

#include <cstdio>
#include <filesystem>
#include <iostream>

#include <allegro5/allegro.h>

#include "../Config.h"
#include "../Vehicle.h"

Bullet::Bullet(Vehicle* v)
{
    source_ = "image/board/bullet.tga";
    if (!loadBitmap())
        exit(0);
    direction_ = v->getDirection();
    speed_ = v->getSpeed();
    power_ = v->getPower();
    x_ = v->getX() + Config::elementSize / 2 - 3;
    y_ = v->getY() + Config::elementSize / 2 - 3;
    vehicle_ = v;
}

Bullet::~Bullet()
{
    al_destroy_bitmap(bmp_);
    try
    {
        vehicle_->resetFire();
    }
    catch (...)
    {
    }
    std::cout << "Bullet: " << static_cast<int>(getTankType())
              << " is deleted\n";
}

bool Bullet::loadBitmap()
{
    if (!std::filesystem::exists(source_))
        return false;

    bmp_ = al_load_bitmap(source_);  //, palette);
    return true;
}

ALLEGRO_BITMAP* Bullet::display() const { return bmp_; }

TankType Bullet::getTankType() const { return vehicle_->getTankType(); }

int Bullet::getPower() const { return power_; }

int Bullet::getSpeed() const { return speed_; }

int Bullet::getDirection() const { return direction_; }

int Bullet::getX() const { return x_; }

int Bullet::getY() const { return y_; }

int Bullet::getCenterX() const { return x_ + 3; }

int Bullet::getCenterY() const { return y_ + 3; }

void Bullet::setX(int newX) { x_ = newX; }

void Bullet::setY(int newY) { y_ = newY; }

int Bullet::getDirectionX() const
{
    if (direction_ == 1)
        return 1;
    if (direction_ == 3)
        return -1;
    return 0;
}

int Bullet::getDirectionY() const
{
    if (direction_ == 0)
        return -1;
    if (direction_ == 2)
        return 1;
    return 0;
}
