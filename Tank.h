#pragma once

#include <ctime>

#include "Direction.h"
#include "Drawable.h"
#include "ResourceType.h"
#include "TankType.h"

class Map;
class Resources;

class Tank : public Drawable
{
public:
    Tank(TankType tankType, Point point);

    void draw(const Screen& screen) const override;
    ResourceType getResourceType() const override;
    Point getCenter() const override;

    void move(Direction direction);
    void moveRandom(Map& map);
    Direction getDirection() const;
    bool canFire();
    bool destroy(unsigned int);
    unsigned int getSpeed() const;
    unsigned int getPower() const;
    void resetFire();
    void setType(TankType tankType);
    TankType getTankType() const;
    void go();
    int getDirectionX() const;
    int getDirectionY() const;
    bool isPlayerControlled() const;

    void applyPowerUp(ResourceType powerUpType);

    bool isWithin(Point point) const;

private:
    void setSpeedUp();
    void addLife();
    void setMaxArmor();
    unsigned int getMaxArmor() const;
    constexpr double pi() const;
    void resetState();

    static const int wayX_[4];
    static const int wayY_[4];
    static const unsigned int powers_[8];
    static const unsigned int armors_[8];
    static const unsigned int speeds_[8];

    Direction direction_;
    TankType type_;
    unsigned int armor_;
    unsigned int power_;
    unsigned int speed_;
    unsigned int maxArmor_;
    time_t lastFire_{0};
    unsigned int lives_{1};
    unsigned int initialX_;
    unsigned int initialY_;
};
