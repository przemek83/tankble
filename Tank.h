#pragma once

#include <ctime>
#include <map>

#include "Direction.h"
#include "Drawable.h"
#include "ResourceType.h"
#include "TankType.h"

class Map;
class Resources;
class Bullet;

class Tank : public Drawable
{
public:
    Tank(TankType tankType, Point point);

    void draw(const Screen& screen) const override;
    ResourceType getResourceType() const override;
    Point getCenter() const override;

    void setDirection(Direction direction);
    Direction getDirection() const;
    bool canFire();
    bool hit(unsigned int power);
    unsigned int getSpeed() const;
    unsigned int getPower() const;
    void resetFire();
    TankType getTankType() const;
    void move(Point point);
    bool isPlayerControlled() const;
    Bullet fire() const;

    std::pair<int, int> getNextExpectedPosition();

    void applyPowerUp(ResourceType powerUpType);

    bool isWithin(Point point) const;

private:
    void setType(TankType tankType);

    int getDirectionX() const;
    int getDirectionY() const;

    void setSpeedUp();
    void addLife();
    void respawn();

    struct Stats
    {
        unsigned int power;
        unsigned int armor;
        unsigned int speed;
    };

    std::map<TankType, Stats> typesStats_{
        {TankType::PLAYER_TIER_1, {2, 8, 4}},
        {TankType::PLAYER_TIER_2, {4, 16, 4}},
        {TankType::PLAYER_TIER_3, {8, 32, 6}},
        {TankType::PLAYER_TIER_4, {16, 64, 8}},
        {TankType::ENEMY_TIER_1, {1, 4, 4}},
        {TankType::ENEMY_TIER_2, {2, 8, 4}},
        {TankType::ENEMY_TIER_3, {4, 16, 6}},
        {TankType::ENEMY_TIER_4, {8, 32, 8}}};

    Direction direction_;
    TankType type_;
    Stats stats_;
    time_t lastFire_{0};
    unsigned int lives_{1};
    unsigned int initialX_;
    unsigned int initialY_;
};
