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
    ALLEGRO_BITMAP* display() const;

private:
    int getLevel();
    void setLevel(int);
    void setVehicle(Vehicle*);

    ALLEGRO_FONT* font_;
    int x_;
    int y_;
    int ptanks_;
    int plevel_;
    ALLEGRO_BITMAP* buffer_;
    Vehicle* vehicle_;
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
