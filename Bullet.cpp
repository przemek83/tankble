#include "Bullet.h"

#include "Config.h"
#include "Direction.h"
#include "Screen.h"

Bullet::Bullet(Point startingPoint, unsigned int speed, TankType tankType,
               unsigned int power, Direction direction)
    : Drawable({startingPoint.x - Config::getInstance().getBulletSize() / 2,
                startingPoint.y - Config::getInstance().getBulletSize() / 2}),
      tankType_(tankType),
      direction_(direction),
      speed_(speed),
      power_(power)
{
}

TankType Bullet::getTankType() const { return tankType_; }

unsigned int Bullet::getPower() const { return power_; }

unsigned int Bullet::getSpeed() const { return speed_; }

Point Bullet::getCenter() const
{
    return {getX() + Config::getInstance().getBulletSize() / 2,
            getY() + Config::getInstance().getBulletSize() / 2};
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
                 getDirectionX() * static_cast<int>(getSpeed())};
    const int py{static_cast<int>(getY()) +
                 getDirectionY() * static_cast<int>(getSpeed())};
    if (!isValid(px, py))
        return false;
    setX(static_cast<unsigned int>(px));
    setY(static_cast<unsigned int>(py));
    return true;
}

void Bullet::draw(const Screen& screen) const
{
    screen.drawScaledBitmap(getResourceType(), getX(), getY(),
                            Config::getInstance().getBulletSize());
}

ResourceType Bullet::getResourceType() const { return ResourceType::BULLET; }

bool Bullet::isValid(int newX, int newY)
{
    const unsigned int bulletSize{Config::getInstance().getBulletSize()};
    const unsigned int maxCoordinate{Config::getInstance().getTileSize() *
                                         Config::getInstance().getTileCount() -
                                     bulletSize};
    return newX < maxCoordinate && newY < maxCoordinate && newY >= 0 &&
           newX >= 0;
}
