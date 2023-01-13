#pragma once

#include "../ResourceType.h"
#include "../TankType.h"

class Tank;

class Bullet
{
public:
    explicit Bullet(const Tank& tank);
    ~Bullet();

    Bullet& operator=(const Bullet& other) = delete;
    Bullet(const Bullet& other) = delete;

    Bullet& operator=(Bullet&& other) = delete;
    Bullet(Bullet&& other) = delete;

    TankType getTankType() const;
    int getPower() const;
    int getSpeed() const;
    int getDirection() const;
    int getX() const;
    int getY() const;

    int getCenterX() const;
    int getCenterY() const;
    void setX(int newX);
    void setY(int newY);
    int getDirectionX() const;
    int getDirectionY() const;

    static ResourceType getResourceType();

private:
    TankType tankType_;
    int direction_;
    int speed_;
    int power_;
    int x_;
    int y_;
};
