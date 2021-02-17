#pragma once

#include <allegro5/allegro.h>
#include "config.h"
#include "map.h"
#include "vehicle.h"

class Game
{
private:
    ALLEGRO_BITMAP* buffer;
    //    int cursor_x;
    //    int cursor_y;
    bool gameOver;
    int ids[3];

public:
    // constructor
    Game();
    ~Game();
    // for tests
    void updateScreen();
    void getMouseInfo();
    //    void createMenu();
    //    int createMenuNew();
    //    int createMenuLoad();
    //    int createMenuOptions();
    //    int createMenuGame();
    //    int endMenu();
    int fullScreen();
    int windowedScreen();
    int startGame();
    void movement(Vehicle*, Map*);
    Player* player;
    Map* mapa;
    void display();
    void displayPlayer();
    void control();
};

void controlz(void*);
void displayz(void*);
void displayPlayerz(void*);
