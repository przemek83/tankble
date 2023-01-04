#pragma once

#include "Vehicle.h"

class Screen;

class Player
{
public:
    Player();

    void loadVehicle(Vehicle*);
    int getTanks();

    void setTanks(int);

    Vehicle* getVehicle();
    Vehicle* killVehicle();

private:
    int getLevel();
    void setLevel(int);
    void setVehicle(Vehicle*);

    int x_;
    int y_;
    int ptanks_;
    int plevel_;
    Vehicle* vehicle_;
};

class Lose
{
};

class Win : public Lose
{
};
