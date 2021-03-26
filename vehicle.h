#pragma once

#include <vector>

#include <allegro5/allegro.h>
#include "config.h"
#include "map/tile.h"

class Vehicle
{
public:
    Vehicle(int tankType, unsigned int x, unsigned int y);
    ~Vehicle();
    ALLEGRO_BITMAP* display();
    int getId();
    void move(int);
    int getX();
    int getY();
    void setX(int);
    void setY(int);
    void moveRandom(void*);
    int getDirection();
    void fire(void*);
    bool destroy(int);
    int getSpeed();
    int getPower();
    void resetFire();
    void setType(int);
    void setMaxArmor();
    int getType();
    void setSpeedUp();
    void go();
    int getDirectionX();
    int getDirectionY();

private:
    int directionX();
    int directionY();
    void setArmor(int);
    int getArmor();
    bool canFly();
    bool canDrive();
    int getMaxArmor();
    bool loadBitmaps(int tankType);

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
    bool fly_;
    bool drive_;
    time_t lastFire_;
    int maxArmor_;
    ALLEGRO_BITMAP* bmp_[4];
};
