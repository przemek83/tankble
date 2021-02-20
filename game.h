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
    void updateScreen();
    void getMouseInfo();
    int fullScreen();
    int windowedScreen();
    int startGame();
    void movement(Vehicle*, Map*);
    Player* player{nullptr};
    Map* mapa{nullptr};
    void display();
    void displayPlayer();
    void control();

private:
    bool userWantToExit(const ALLEGRO_EVENT& event) const;

    ALLEGRO_BITMAP* buffer{nullptr};
    bool gameOver{false};
    int ids[3]{};
};

void controlz(void*);
void displayz(void*);
void displayPlayerz(void*);
