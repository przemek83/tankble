#include "Bullet.h"

#include "Config.h"
#include "Direction.h"
#include "PointUtils.h"
#include "Screen.h"

Bullet::Bullet(Point startingPoint, unsigned int speed, bool playerOrigin,
               unsigned int power, Direction direction)
    : Drawable({startingPoint.x - Config::getInstance().getBulletSize() / 2,
                startingPoint.y - Config::getInstance().getBulletSize() / 2}),
      size_(Config::getInstance().getBulletSize()),
      playerOrigin_(playerOrigin),
      direction_(direction),
      speed_(speed),
      power_(power)
{
}

bool Bullet::isPlayerOrigin() const { return playerOrigin_; }

unsigned int Bullet::getPower() const { return power_; }

Point Bullet::getCenter() const
{
    return {getX() + size_ / 2, getY() + size_ / 2};
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
    const int px{static_cast<int>(getX()) +
                 getDirectionX() * static_cast<int>(speed_)};
    const int py{static_cast<int>(getY()) +
                 getDirectionY() * static_cast<int>(speed_)};

    if (!PointUtils::isValidPoint(px, py, size_))
        return false;

    setLocation(PointUtils::pointFromSigned(px, py));

    return true;
}

void Bullet::draw(const Screen& screen) const
{
    screen.drawScaledSquareBitmap(getResourceType(), getX(), getY(), size_);
}

ResourceType Bullet::getResourceType() const { return ResourceType::BULLET; }
