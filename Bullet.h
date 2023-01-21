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
    unsigned int getPower() const;
    unsigned int getSpeed() const;

    unsigned int getCenterX() const;
    unsigned int getCenterY() const;
    int getDirectionX() const;
    int getDirectionY() const;

    void draw(const Screen& screen) const override;
    ResourceType getResourceType() const override;

private:
    TankType tankType_;
    int direction_;
    unsigned int speed_;
    unsigned int power_;
};
