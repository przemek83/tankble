#pragma once

#include <cmath>
#include <string>
#include <vector>
#include "TankType.h"

#include <allegro5/allegro.h>

class Map;

class Tank
{
public:
    Tank(TankType tankType, unsigned int x, unsigned int y);
    ~Tank();
    ALLEGRO_BITMAP* display();
    void move(int);
    int getX() const;
    int getY() const;
    void setX(int);
    void setY(int);
    void moveRandom(Map& map);
    int getDirection() const;
    void fire(Map& map);
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
    bool loadBitmaps(TankType tankType);
    constexpr double pi() const;
    void resetState();

    static const int wayX_[4];
    static const int wayY_[4];
    static const int powers_[8];
    static const int armors_[8];
    static const int speeds_[8];
    static const int directions_[8];
    const std::vector<std::string> tankTypesPaths_{
        "image/board/tank_tier1.tga",       "image/board/tank_tier2.tga",
        "image/board/tank_tier3.tga",       "image/board/tank_tier4.tga",
        "image/board/tank_tier1_enemy.tga", "image/board/tank_tier2_enemy.tga",
        "image/board/tank_tier3_enemy.tga", "image/board/tank_tier4_enemy.tga"};
    int direction_;
    int x_;
    int y_;
    TankType type_;
    int armor_;
    int power_;
    int speed_;
    int maxArmor_;
    time_t lastFire_{0};
    ALLEGRO_BITMAP* bmp_[4];
    unsigned int lives_{1};
    unsigned int initialX_;
    unsigned int initialY_;
};
