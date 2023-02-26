#include "Tank.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <iostream>

#include "Bullet.h"
#include "Config.h"
#include "Direction.h"
#include "Screen.h"
#include "TankType.h"

Tank::Tank(TankType tankType, Point point)
    : Drawable(point), initialX_(point.x), initialY_(point.y)
{
    setType(tankType);
    direction_ = (isPlayerControlled() ? Direction::UP : Direction::DOWN);
}

void Tank::draw(const Screen& screen) const
{
    const unsigned int rightAngle{90};
    screen.drawScaledBitmapWithRotation(
        getResourceType(), getX(), getY(), Config::getInstance().getTileSize(),
        rightAngle * static_cast<unsigned int>(getDirection()));
}

ResourceType Tank::getResourceType() const
{
    return static_cast<ResourceType>(
        static_cast<unsigned char>(ResourceType::PLAYER_TANK_TIER_1) +
        static_cast<unsigned char>(type_));
}

Point Tank::getCenter() const
{
    const unsigned int middle{Config::getInstance().getTileSize() / 2};
    return {getX() + middle, getY() + middle};
}

void Tank::setType(TankType tankType)
{
    type_ = tankType;
    stats_ = typesStats_[tankType];
}

void Tank::setDirection(Direction direction) { direction_ = direction; }

bool Tank::canFire()
{
    const time_t ti = time(nullptr);
    if (difftime(ti, lastFire_) > 1.0)
    {
        lastFire_ = ti;
        return true;
    }

    return false;
}

bool Tank::hit(unsigned int power)
{
    if (power > stats_.armor)
        stats_.armor = 0;
    else
        stats_.armor -= power;

    if (stats_.armor == 0)
    {
        if (stats_.lives <= 1)
            return true;
        stats_.lives--;
        respawn();
    }
    return false;
}

void Tank::setSpeedUp() { stats_.speed++; }

Direction Tank::getDirection() const { return direction_; }

int Tank::getDirectionX() const
{
    if (getDirection() == Direction::LEFT)
        return -1;

    if (getDirection() == Direction::RIGHT)
        return 1;

    return 0;
}

int Tank::getDirectionY() const
{
    if (getDirection() == Direction::UP)
        return -1;

    if (getDirection() == Direction::DOWN)
        return 1;

    return 0;
}

bool Tank::isPlayerControlled() const
{
    return type_ == TankType::PLAYER_TIER_1 ||
           type_ == TankType::PLAYER_TIER_2 ||
           type_ == TankType::PLAYER_TIER_3 || type_ == TankType::PLAYER_TIER_4;
}

TankStats Tank::getStats() const { return stats_; }

Bullet Tank::fire() const
{
    return {getCenter(), stats_.speed, isPlayerControlled(), stats_.attackPower,
            getDirection()};
}

std::pair<int, int> Tank::getNextExpectedPosition()
{
    std::pair<int, int> nextPosition{
        static_cast<int>(getX()) + getDirectionX(),
        static_cast<int>(getY()) + getDirectionY()};
    return nextPosition;
}

void Tank::addLife() { stats_.lives++; }

void Tank::applyPowerUp(ResourceType powerUpType)
{
    switch (powerUpType)
    {
        case ResourceType::SHIELD_UP:
            stats_.armor = typesStats_[type_].armor;
            break;

        case ResourceType::TIER_UP:
            if (static_cast<int>(type_) < 3)
                setType(static_cast<TankType>(static_cast<int>(type_) + 1));
            break;

        case ResourceType::SPEED_UP:
            setSpeedUp();
            break;

        case ResourceType::LIFE_UP:
            addLife();
            break;

        default:
            break;
    }
}

bool Tank::isWithin(Point point) const
{
    const unsigned int tileSize{Config::getInstance().getTileSize()};
    return point.x >= getX() && point.x < getX() + tileSize &&
           point.y >= getY() && point.y < getY() + tileSize;
}

void Tank::resetFire() { lastFire_--; }

void Tank::move(Point point)
{
    setX(point.x);
    setY(point.y);
}

void Tank::respawn()
{
    setX(initialX_);
    setY(initialY_);
    if (isPlayerControlled())
        setType(TankType::PLAYER_TIER_1);
    direction_ = (isPlayerControlled() ? Direction::UP : Direction::DOWN);
}
