#pragma once

#include <allegro5/allegro.h>
#include "config.h"
#include "map/tile.h"

class Vehicle
{
public:
    Vehicle(int, uint, uint);
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

    static const int wayX[4];
    static const int wayY[4];
    static const int powers[8];
    static const int armors[8];
    static const int speeds[8];
    static const int ids[8];
    static const int directions[8];
    const std::vector<std::string> tankTypesPaths{
        "image/board/tank_tier1.tga",       "image/board/tank_tier2.tga",
        "image/board/tank_tier3.tga",       "image/board/tank_tier4.tga",
        "image/board/tank_tier1_enemy.tga", "image/board/tank_tier2_enemy.tga",
        "image/board/tank_tier3_enemy.tga", "image/board/tank_tier4_enemy.tga"};
    int direction;
    int x;
    int y;
    int id;
    int armor;
    int power;
    int speed;
    bool fly;
    bool drive;
    time_t lastFire;
    int maxArmor;
    bool loadBitmaps(int tankType);
    ALLEGRO_BITMAP* bmp[4];
};
