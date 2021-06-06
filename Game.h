#pragma once

#include <allegro5/allegro.h>
#include "Config.h"
#include "Map.h"
#include "Vehicle.h"

class Screen;

class Game
{
public:
    Game(Screen& screen);
    ~Game();

    Game& operator=(const Game& other) = delete;
    Game(const Game& other) = delete;

    Game& operator=(Game&& other) = delete;
    Game(Game&& other) = delete;

    bool startGame();

private:
    bool userWantToExit(const ALLEGRO_EVENT& event) const;

    bool userWantToQuit(const ALLEGRO_EVENT& event) const;

    void movement(Vehicle*, Map*);
    void display();
    void displayPlayer(const Player& player);
    void control();

    void drawEndOfGame(const std::string& text);

    Screen& screen_;
    Map* map_{nullptr};
    ALLEGRO_BITMAP* buffer_{nullptr};
    bool gameOver_{false};
};
