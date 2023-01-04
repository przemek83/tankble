#pragma once

#include <string>

#include <allegro5/allegro.h>

class Vehicle;
class Map;
class Screen;

class Game
{
public:
    explicit Game(Screen& screen);

    bool play();

private:
    bool userWantToExit(const ALLEGRO_EVENT& event) const;

    bool userWantToQuit(const ALLEGRO_EVENT& event) const;

    void movement(Vehicle* myTank, Map& map);
    void drawMap(Map& map);
    void drawStatusPlaceholder();
    void control(Map& map);

    void drawEndOfGame(const std::string& text);

    Screen& screen_;
    ALLEGRO_BITMAP* buffer_{nullptr};
    bool gameOver_{false};
};
