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

unsigned int Bullet::getPower() const { return power_; }

unsigned int Bullet::getSpeed() const { return speed_; }

unsigned int Bullet::getCenterX() const { return getX() + 3; }

unsigned int Bullet::getCenterY() const { return getY() + 3; }

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

bool Bullet::move()
{
    const int px{static_cast<int>(getX()) +
                 getDirectionX() * static_cast<int>(getSpeed())};
    const int py{static_cast<int>(getY()) +
                 getDirectionY() * static_cast<int>(getSpeed())};
    if (!isValid(px, py))
        return false;
    setX(px);
    setY(py);
    return true;
}

void Bullet::draw(const Screen& screen) const
{
    screen.drawScaledBitmap(getResourceType(), getX(), getY(),
                            Config::BULLET_SIZE);
}

ResourceType Bullet::getResourceType() const { return ResourceType::BULLET; }

bool Bullet::isValid(int newX, int newY)
{
    constexpr int bulletSize{Config::BULLET_SIZE};
    constexpr int maxCoordinate{Config::elementSize * Config::mapSize -
                                bulletSize};
    return newX < maxCoordinate && newY < maxCoordinate && newY >= 0 &&
           newX >= 0;
}
