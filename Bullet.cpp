#include "Bullet.h"

#include <iostream>

#include "Config.h"
#include "Tank.h"

Bullet::Bullet(const Tank& tank) : tankType_(tank.getTankType())
{
    direction_ = tank.getDirection();
    speed_ = tank.getSpeed();
    power_ = tank.getPower();
    x_ = tank.getX() + Config::elementSize / 2 - 3;
    y_ = tank.getY() + Config::elementSize / 2 - 3;
}

Bullet::~Bullet()
{
    std::cout << "Bullet: " << static_cast<int>(getTankType())
              << " is deleted\n";
}

TankType Bullet::getTankType() const { return tankType_; }

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

ResourceType Bullet::getResourceType() { return ResourceType::BULLET; }
