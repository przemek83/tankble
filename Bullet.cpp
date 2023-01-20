#include "Bullet.h"

#include <iostream>

#include "Config.h"
#include "Screen.h"
#include "Tank.h"

Bullet::Bullet(const Tank& tank)
    : Drawable({tank.getX() + Config::elementSize / 2 - 3,
                tank.getY() + Config::elementSize / 2 - 3}),
      tankType_(tank.getTankType())
{
    direction_ = tank.getDirection();
    speed_ = tank.getSpeed();
    power_ = tank.getPower();
}

TankType Bullet::getTankType() const { return tankType_; }

int Bullet::getPower() const { return power_; }

int Bullet::getSpeed() const { return speed_; }

int Bullet::getDirection() const { return direction_; }

int Bullet::getCenterX() const { return getX() + 3; }

int Bullet::getCenterY() const { return getY() + 3; }

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

void Bullet::draw(const Screen& screen) const
{
    screen.drawScaledBitmap(getResourceType(), getX(), getY(),
                            Config::BULLET_SIZE);
}

ResourceType Bullet::getResourceType() const { return ResourceType::BULLET; }
