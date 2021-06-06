#pragma once

#include <cmath>
#include <vector>

#include <allegro5/allegro.h>

#include "Config.h"
#include "map/Tile.h"

class Vehicle
{
public:
    Vehicle(int tankType, unsigned int x, unsigned int y);
    ~Vehicle();
    ALLEGRO_BITMAP* display();
    int getId() const;
    void move(int);
    int getX() const;
    int getY() const;
    void setX(int);
    void setY(int);
    void moveRandom(void*);
    int getDirection() const;
    void fire(void*);
    bool destroy(int);
    int getSpeed() const;
    int getPower() const;
    void resetFire();
    void setType(int);
    void setMaxArmor();
    int getType() const;
    void setSpeedUp();
    void go();
    int getDirectionX() const;
    int getDirectionY() const;

private:
    int directionX();
    int directionY();
    void setArmor(int);
    int getArmor() const;
    int getMaxArmor() const;
    bool loadBitmaps(int tankType);
    constexpr double pi() const;

    static const int wayX_[4];
    static const int wayY_[4];
    static const int powers_[8];
    static const int armors_[8];
    static const int speeds_[8];
    static const int ids_[8];
    static const int directions_[8];
    const std::vector<std::string> tankTypesPaths_{
        "image/board/tank_tier1.tga",       "image/board/tank_tier2.tga",
        "image/board/tank_tier3.tga",       "image/board/tank_tier4.tga",
        "image/board/tank_tier1_enemy.tga", "image/board/tank_tier2_enemy.tga",
        "image/board/tank_tier3_enemy.tga", "image/board/tank_tier4_enemy.tga"};
    int direction_;
    int x_;
    int y_;
    int id_;
    int armor_;
    int power_;
    int speed_;
    int maxArmor_;
    time_t lastFire_{0};
    ALLEGRO_BITMAP* bmp_[4];
};
