#include "Bullet.h"

#include "Config.h"
#include "Direction.h"
#include "PointUtils.h"
#include "Screen.h"
#include "Utils.h"

Bullet::Bullet(Point startingPoint, int speed, bool playerOrigin, int power,
               Direction direction)
    : Drawable({startingPoint.x_ -
                    (utils::getMidpoint(Config::getInstance().getBulletSize())),
                startingPoint.y_ -
                    utils::getMidpoint(Config::getInstance().getBulletSize())}),
      size_(Config::getInstance().getBulletSize()),
      playerOrigin_(playerOrigin),
      direction_(direction),
      speed_(speed),
      power_(power)
{
}

bool Bullet::isPlayerOrigin() const { return playerOrigin_; }

int Bullet::getPower() const { return power_; }

Point Bullet::getCenter() const
{
    return {getX() + utils::getMidpoint(size_),
            getY() + utils::getMidpoint(size_)};
}

int Bullet::getDirectionX() const
{
    if (direction_ == Direction::RIGHT)
        return 1;
    if (direction_ == Direction::LEFT)
        return -1;
    return 0;
}

int Bullet::getDirectionY() const
{
    if (direction_ == Direction::UP)
        return -1;
    if (direction_ == Direction::DOWN)
        return 1;
    return 0;
}

bool Bullet::move()
{
    const int px{getX() + (getDirectionX() * speed_)};
    const int py{getY() + (getDirectionY() * speed_)};

    if (!point_utils::isValidPoint(px, py, size_))
        return false;

    setLocation({px, py});

    return true;
}

void Bullet::draw(const Display& display) const
{
    display.drawScaledSquareBitmap(getResourceType(), getX(), getY(), size_);
}

ResourceType Bullet::getResourceType() const { return ResourceType::BULLET; }
