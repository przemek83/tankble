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

    TankType tankType_;
    Direction direction_;
    unsigned int speed_;
    unsigned int power_;
};
