#pragma once

#include "Drawable.h"
#include "ResourceType.h"
#include "TankType.h"

class Tank;

class Bullet : public Drawable
{
public:
    explicit Bullet(const Tank& tank);

    TankType getTankType() const;
    int getPower() const;
    int getSpeed() const;
    int getDirection() const;

    int getCenterX() const;
    int getCenterY() const;
    int getDirectionX() const;
    int getDirectionY() const;

    void draw(const Screen& screen) const override;
    ResourceType getResourceType() const override;

private:
    TankType tankType_;
    int direction_;
    int speed_;
    int power_;
};
