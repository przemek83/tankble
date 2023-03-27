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
    bool canFire(time_t currentTime);
    void resetFire();

    bool hit(unsigned int power);
    void move(Point point);
    bool isPlayerControlled() const;

    TankStats getStats() const;

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

    static const unsigned int BASIC_ATTACK{1};
    static const unsigned int BASIC_HEALTH{1};
    static const unsigned int BASIC_SPEED{4};
    static const unsigned int SINGLE_LIFE{1};

    std::map<TankType, TankStats> typesStats_{
        {TankType::PLAYER_TIER_1,
         {BASIC_ATTACK, BASIC_HEALTH, BASIC_SPEED, 2 * SINGLE_LIFE}},
        {TankType::PLAYER_TIER_2,
         {2 * BASIC_ATTACK, 2 * BASIC_HEALTH, BASIC_SPEED, 2 * SINGLE_LIFE}},
        {TankType::PLAYER_TIER_3,
         {3 * BASIC_ATTACK, 3 * BASIC_HEALTH, BASIC_SPEED + 2,
          2 * SINGLE_LIFE}},
        {TankType::PLAYER_TIER_4,
         {4 * BASIC_ATTACK, 4 * BASIC_HEALTH, BASIC_SPEED + 4,
          2 * SINGLE_LIFE}},
        {TankType::ENEMY_TIER_1,
         {BASIC_ATTACK, BASIC_HEALTH, BASIC_SPEED, SINGLE_LIFE}},
        {TankType::ENEMY_TIER_2,
         {2 * BASIC_ATTACK, 2 * BASIC_HEALTH, BASIC_SPEED, SINGLE_LIFE}},
        {TankType::ENEMY_TIER_3,
         {3 * BASIC_ATTACK, 3 * BASIC_HEALTH, BASIC_SPEED + 2, SINGLE_LIFE}},
        {TankType::ENEMY_TIER_4,
         {4 * BASIC_ATTACK, 4 * BASIC_HEALTH, BASIC_SPEED + 4, SINGLE_LIFE}}};

    Direction direction_;
    TankType type_;
    TankStats stats_;
    time_t lastFire_{0};
    const unsigned int initialX_;
    const unsigned int initialY_;
};
