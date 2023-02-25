#pragma once

#include <ctime>
#include <map>

#include "Direction.h"
#include "Drawable.h"
#include "ResourceType.h"
#include "TankStats.h"
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

    Bullet fire() const;
    bool canFire();
    void resetFire();

    bool hit(unsigned int power);
    void move(Point point);
    bool isPlayerControlled() const;
    unsigned int getLives() const;

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

    std::map<TankType, TankStats> typesStats_{
        {TankType::PLAYER_TIER_1, {2, 8, 4, 2}},
        {TankType::PLAYER_TIER_2, {4, 16, 4, 2}},
        {TankType::PLAYER_TIER_3, {8, 32, 6, 2}},
        {TankType::PLAYER_TIER_4, {16, 64, 8, 2}},
        {TankType::ENEMY_TIER_1, {1, 4, 4, 1}},
        {TankType::ENEMY_TIER_2, {2, 8, 4, 1}},
        {TankType::ENEMY_TIER_3, {4, 16, 6, 1}},
        {TankType::ENEMY_TIER_4, {8, 32, 8, 1}}};

    Direction direction_;
    TankType type_;
    TankStats stats_;
    time_t lastFire_{0};
    const unsigned int initialX_;
    const unsigned int initialY_;
};
