#include "Tank.h"

#include <cmath>

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
    stats_.speed = getCalculatedSpeed(Config::getInstance().getSpeedFactor());
}

void Tank::setDirection(Direction direction) { direction_ = direction; }

bool Tank::canFire(TimePoint currentTime) const
{
    using std::chrono::duration_cast;
    using std::chrono::seconds;
    return duration_cast<seconds>(currentTime - lastFire_) >=
           Config::getInstance().getFireDelay();
}

bool Tank::hit(unsigned int power)
{
    if (power > stats_.shield)
        stats_.shield = 0;
    else
        stats_.shield -= power;

    if (stats_.shield == 0)
    {
        if (stats_.lives <= 1)
        {
            stats_.lives = 0;
            return true;
        }
        const unsigned int livesLeft = stats_.lives - 1;
        respawn();
        stats_.lives = livesLeft;
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

Bullet Tank::fire(TimePoint currentTime)
{
    lastFire_ = currentTime;
    return {getCenter(), stats_.speed + 2, isPlayerControlled(),
            stats_.attackPower, getDirection()};
}

std::pair<int, int> Tank::getNextExpectedPosition()
{
    const int speed{static_cast<int>(stats_.speed)};
    std::pair<int, int> nextPosition{
        static_cast<int>(getX()) + getDirectionX() * speed,
        static_cast<int>(getY()) + getDirectionY() * speed};
    return nextPosition;
}

void Tank::addLife() { stats_.lives++; }

void Tank::applyPowerUp(ResourceType powerUpType)
{
    switch (powerUpType)
    {
        case ResourceType::SHIELD_UP:
            stats_.shield = typesStats_[type_].shield;
            break;

        case ResourceType::TIER_UP:
            if (static_cast<int>(type_) < 3)
            {
                const TankStats oldStats{stats_};
                setType(static_cast<TankType>(static_cast<int>(type_) + 1));
                stats_.lives = oldStats.lives;
                stats_.speed = std::max(oldStats.speed, stats_.speed);
            }
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

void Tank::resetFire() { lastFire_ = TimePoint(); }

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

unsigned int Tank::getCalculatedSpeed(float speedFactor) const
{
    const unsigned int tileSize{Config::getInstance().getTileSize()};
    float speed{std::round(static_cast<float>(stats_.speed) * speedFactor)};
    if (!isPlayerControlled())
        while (speed >= 1 && tileSize % static_cast<unsigned int>(speed) != 0)
            speed -= 1;
    return std::max(1U, static_cast<unsigned int>(speed));
}
