#pragma once

#include <allegro5/allegro.h>
#include "config.h"
#include "map.h"
#include "vehicle.h"

class Game
{
public:
    Game();
    ~Game();
    int startGame();

private:
    bool userWantToExit(const ALLEGRO_EVENT& event) const;
    void movement(Vehicle*, Map*);
    void display();
    void displayPlayer();
    void control();

    Player* player_{nullptr};
    Map* map_{nullptr};
    ALLEGRO_BITMAP* buffer_{nullptr};
    bool gameOver_{false};
    int ids_[3]{};
};
