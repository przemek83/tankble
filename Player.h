#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

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
    ALLEGRO_BITMAP* display(Screen& screen) const;

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
};

class Win : public Lose
{
};
