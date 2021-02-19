#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
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

private:
    ALLEGRO_FONT* font_;
    int x;
    int y;
    int ptanks;
    int plevel;
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
