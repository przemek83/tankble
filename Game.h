#pragma once

#include <string>

#include <allegro5/allegro.h>

class Vehicle;
class Map;
class Player;
class Screen;

class Game
{
public:
    explicit Game(Screen& screen);
    ~Game();

    Game& operator=(const Game& other) = delete;
    Game(const Game& other) = delete;

    Game& operator=(Game&& other) = delete;
    Game(Game&& other) = delete;

    bool play();

private:
    bool userWantToExit(const ALLEGRO_EVENT& event) const;

    bool userWantToQuit(const ALLEGRO_EVENT& event) const;

    void movement(Vehicle*, Map*);
    void drawMap();
    void drawStatusPlaceholder();
    void control();

    void drawEndOfGame(const std::string& text);

    Screen& screen_;
    Map* map_{nullptr};
    ALLEGRO_BITMAP* buffer_{nullptr};
    bool gameOver_{false};
};
