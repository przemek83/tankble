#pragma once

#include <allegro5/allegro.h>
#include "vehicle.h"

class Player
{
public:
    Player();
    ~Player();
    void loadVehicle(Vehicle*);
    int getArmor();
    int getSpeed();
    int getLevel();
    int getTanks();
    int getPower();

    void setLevel(int);
    void setTanks(int);

    Vehicle* getVehicle();
    Vehicle* killVehicle();
    void setVehicle(Vehicle*);
    ALLEGRO_BITMAP* getVehicleBitmap();
    ALLEGRO_BITMAP* display();
    bool loadBitmap();

private:
    int x;
    int y;
    int ptanks;
    int plevel;
    const char* source;
    ALLEGRO_BITMAP* bmp;
    ALLEGRO_BITMAP* buffer;
    Vehicle* vehicle;
};

class Lose
{
public:
    void display();
};

class Win : public Lose
{
public:
    void display();
};
