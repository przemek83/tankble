#pragma once

#include <ctime>

#include "Drawable.h"
#include "ResourceType.h"
#include "TankType.h"

class Map;
class Resources;

class Tank : public Drawable
{
public:
    Tank(TankType tankType, unsigned int x, unsigned int y);

    void draw(const Screen& screen) const override;
    ResourceType getResourceType() const override;

    void move(int);
    void moveRandom(Map& map);
    int getDirection() const;
    bool canFire();
    bool destroy(int);
    int getSpeed() const;
    int getPower() const;
    void resetFire();
    void setType(TankType tankType);
    TankType getTankType() const;
    void go();
    int getDirectionX() const;
    int getDirectionY() const;
    bool isPlayerControlled() const;

    void applyPowerUp(ResourceType powerUpType);

private:
    void setSpeedUp();
    void addLife();
    void setMaxArmor();
    int getMaxArmor() const;
    constexpr double pi() const;
    void resetState();

    static const int wayX_[4];
    static const int wayY_[4];
    static const int powers_[8];
    static const int armors_[8];
    static const int speeds_[8];
    static const int directions_[8];

    int direction_;
    TankType type_;
    int armor_;
    int power_;
    int speed_;
    int maxArmor_;
    time_t lastFire_{0};
    unsigned int lives_{1};
    unsigned int initialX_;
    unsigned int initialY_;
};
