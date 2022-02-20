#pragma once

#include "Vehicle.h"

class Screen;

class Player
{
public:
    Player();
    ~Player();

    Player& operator=(const Player& other) = delete;
    Player(const Player& other) = delete;

    Player& operator=(Player&& other) = delete;
    Player(Player&& other) = delete;

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
