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
    int getTanks();

    void setTanks(int);

    Vehicle* getVehicle();
    Vehicle* killVehicle();
    ALLEGRO_BITMAP* display();

private:
    int getLevel();
    void setLevel(int);
    void setVehicle(Vehicle*);

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
