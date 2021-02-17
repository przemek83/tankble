#pragma once

#include <allegro5/allegro.h>
#include "config.h"
#include "map/map_element.h"
//#include "map.h"

// using std::vector;

class Vehicle
{
protected:
    static const int wayX[4];
    static const int wayY[4];
    static const int powers[8];
    static const int armors[8];
    static const int speeds[8];
    static const int ids[8];
    static const int directions[8];
    static const char* sources[8][4];
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
    const char** source;
    bool loadBitmaps();
    ALLEGRO_BITMAP* bmp[4];

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
    int directionX();
    int directionY();
    void fire(void*);
    void setArmor(int);
    int getArmor();
    bool canFly();
    bool canDrive();
    bool destroy(int);
    int getMaxArmor();
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
};
