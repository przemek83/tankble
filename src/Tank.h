#pragma once

#include <chrono>
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

    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
    Bullet fire(TimePoint currentTime);
    bool canFire(TimePoint currentTime) const;

    bool hit(int power);
    void move(Point point);
    bool isPlayerControlled() const;

    TankStats getStats() const;

    std::pair<int, int> getNextExpectedPosition() const;

    void applyPowerUp(ResourceType powerUpType);

    bool isWithin(Point point) const;

private:
    void setType(TankType tankType);

    int getDirectionX() const;
    int getDirectionY() const;

    void setSpeedUp();
    void addLife();
    void respawn();

    int getCalculatedSpeed(float speedFactor) const;

    static const int BASIC_ATTACK{1};
    static const int BASIC_HEALTH{1};
    static const int BASIC_SPEED{2};
    static const int SINGLE_LIFE{1};

    std::map<TankType, TankStats> typesStats_{
        {TankType::PLAYER_TIER_1,
         {BASIC_ATTACK, BASIC_HEALTH, BASIC_SPEED, 2 * SINGLE_LIFE}},
        {TankType::PLAYER_TIER_2,
         {2 * BASIC_ATTACK, 2 * BASIC_HEALTH, BASIC_SPEED, 2 * SINGLE_LIFE}},
        {TankType::PLAYER_TIER_3,
         {3 * BASIC_ATTACK, 3 * BASIC_HEALTH, BASIC_SPEED + 1,
          2 * SINGLE_LIFE}},
        {TankType::PLAYER_TIER_4,
         {4 * BASIC_ATTACK, 4 * BASIC_HEALTH, BASIC_SPEED + 2,
          2 * SINGLE_LIFE}},
        {TankType::ENEMY_TIER_1,
         {BASIC_ATTACK, BASIC_HEALTH, BASIC_SPEED, SINGLE_LIFE}},
        {TankType::ENEMY_TIER_2,
         {2 * BASIC_ATTACK, 2 * BASIC_HEALTH, BASIC_SPEED, SINGLE_LIFE}},
        {TankType::ENEMY_TIER_3,
         {3 * BASIC_ATTACK, 3 * BASIC_HEALTH, BASIC_SPEED + 1, SINGLE_LIFE}},
        {TankType::ENEMY_TIER_4,
         {4 * BASIC_ATTACK, 4 * BASIC_HEALTH, BASIC_SPEED + 2, SINGLE_LIFE}}};

    Direction direction_{};
    TankType type_{};
    TankStats stats_{};
    TimePoint lastFire_{TimePoint()};
    const int initialX_{};
    const int initialY_{};
};
