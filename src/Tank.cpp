#include "Tank.h"

#include <cmath>

#include "Bullet.h"
#include "Config.h"
#include "Direction.h"
#include "Screen.h"
#include "TankType.h"

Tank::Tank(TankType tankType, Point point)
    : Drawable(point), initialX_(point.x_), initialY_(point.y_)
{
    setType(tankType);
    direction_ = (isPlayerControlled() ? Direction::UP : Direction::DOWN);
}

void Tank::draw(const Screen& screen) const
{
    const int rightAngle{90};
    screen.drawScaledBitmapWithRotation(
        getResourceType(), getX(), getY(), Config::getInstance().getTileSize(),
        rightAngle * static_cast<int>(getDirection()));
}

ResourceType Tank::getResourceType() const
{
    return static_cast<ResourceType>(
        static_cast<char>(ResourceType::PLAYER_TANK_TIER_1) +
        static_cast<char>(type_));
}

Point Tank::getCenter() const
{
    const int middle{Config::getInstance().getTileSize() / 2};
    return {getX() + middle, getY() + middle};
}

void Tank::setType(TankType tankType)
{
    type_ = tankType;
    stats_ = typesStats_[tankType];
    stats_.speed_ = getCalculatedSpeed(Config::getInstance().getSpeedFactor());
}

void Tank::setDirection(Direction direction) { direction_ = direction; }

bool Tank::canFire(TimePoint currentTime) const
{
    using std::chrono::duration_cast;
    using std::chrono::seconds;
    return duration_cast<seconds>(currentTime - lastFire_) >=
           Config::getInstance().getFireDelay();
}

bool Tank::destroy()
{
    if (stats_.lives_ <= 1)
    {
        stats_.lives_ = 0;
        return true;
    }

    const int livesLeft = stats_.lives_ - 1;
    respawn();
    stats_.lives_ = livesLeft;

    return false;
}

bool Tank::hit(int power)
{
    if (power > stats_.shield_)
        stats_.shield_ = 0;
    else
        stats_.shield_ -= power;

    if (stats_.shield_ != 0)
        return false;

    return destroy();
}

void Tank::setSpeedUp() { ++stats_.speed_; }

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
    return (type_ == TankType::PLAYER_TIER_1) ||
           (type_ == TankType::PLAYER_TIER_2) ||
           (type_ == TankType::PLAYER_TIER_3) ||
           (type_ == TankType::PLAYER_TIER_4);
}

TankStats Tank::getStats() const { return stats_; }

Bullet Tank::fire(TimePoint currentTime)
{
    lastFire_ = currentTime;
    return {getCenter(), stats_.speed_ + 2, isPlayerControlled(),
            stats_.attackPower_, getDirection()};
}

std::pair<int, int> Tank::getNextExpectedPosition() const
{
    const int speed{stats_.speed_};
    const std::pair<int, int> nextPosition{getX() + getDirectionX() * speed,
                                           getY() + getDirectionY() * speed};
    return nextPosition;
}

void Tank::addLife() { ++stats_.lives_; }

void Tank::tierUp()
{
    const TankStats oldStats{stats_};
    setType(static_cast<TankType>(static_cast<int>(type_) + 1));
    stats_.lives_ = oldStats.lives_;
    stats_.speed_ = std::max(oldStats.speed_, stats_.speed_);
}
void Tank::applyPowerUp(ResourceType powerUpType)
{
    switch (powerUpType)
    {
        case ResourceType::SHIELD_UP:
            stats_.shield_ = typesStats_[type_].shield_;
            break;

        case ResourceType::TIER_UP:
            if (type_ != TankType::PLAYER_TIER_4)
                tierUp();
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
    const int tileSize{Config::getInstance().getTileSize()};
    return (point.x_ >= getX()) && (point.x_ < (getX() + tileSize)) &&
           (point.y_ >= getY()) && (point.y_ < (getY() + tileSize));
}

void Tank::move(Point point)
{
    setX(point.x_);
    setY(point.y_);
}

void Tank::respawn()
{
    setX(initialX_);
    setY(initialY_);
    if (isPlayerControlled())
        setType(TankType::PLAYER_TIER_1);
    direction_ = (isPlayerControlled() ? Direction::UP : Direction::DOWN);
}

void Tank::adjustEnemySpeed(float& speed) const
{
    const int tileSize{Config::getInstance().getTileSize()};
    while ((speed >= 1) && ((tileSize % static_cast<int>(speed)) != 0))
        speed -= 1;
}

int Tank::getCalculatedSpeed(float speedFactor) const
{
    float speed{std::round(static_cast<float>(stats_.speed_) * speedFactor)};
    if (!isPlayerControlled())
        adjustEnemySpeed(speed);
    return std::max(1, static_cast<int>(speed));
}
