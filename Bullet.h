#pragma once

#include "Direction.h"
#include "Drawable.h"
#include "ResourceType.h"
#include "TankType.h"

class Tank;

class Bullet : public Drawable
{
public:
    explicit Bullet(const Tank& tank);

    TankType getTankType() const;
    unsigned int getPower() const;

    bool move();

    void draw(const Screen& screen) const override;
    ResourceType getResourceType() const override;
    Point getCenter() const override;

private:
    unsigned int getSpeed() const;
    int getDirectionX() const;
    int getDirectionY() const;
    static bool isValid(int newX, int newY);

    const TankType tankType_;
    const Direction direction_;
    const unsigned int speed_;
    const unsigned int power_;
};
