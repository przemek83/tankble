#pragma once

#include <ctime>

#include "TankType.h"

class Map;
class Resources;

class Tank
{
public:
    Tank(TankType tankType, unsigned int x, unsigned int y);
    ~Tank();

    Tank& operator=(const Tank& other) = delete;
    Tank(const Tank& other) = delete;

    Tank& operator=(Tank&& other) = default;
    Tank(Tank&& other) = default;

    void move(int);
    int getX() const;
    int getY() const;
    void setX(int);
    void setY(int);
    void moveRandom(Map& map);
    int getDirection() const;
    bool canFire();
    bool destroy(int);
    int getSpeed() const;
    int getPower() const;
    void resetFire();
    void setType(TankType tankType);
    void setMaxArmor();
    TankType getTankType() const;
    void setSpeedUp();
    void go();
    int getDirectionX() const;
    int getDirectionY() const;
    bool isPlayerControlled() const;
    void addLife();

private:
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
    int x_;
    int y_;
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
