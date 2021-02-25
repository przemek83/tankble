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

    Player* player{nullptr};
    Map* mapa{nullptr};
    ALLEGRO_BITMAP* buffer{nullptr};
    bool gameOver{false};
    int ids[3]{};
};
