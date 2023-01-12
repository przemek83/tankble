#pragma once

#include <string>

class Tank;
class Map;
class Screen;
union ALLEGRO_EVENT;
struct ALLEGRO_BITMAP;

class Game
{
public:
    explicit Game(Screen& screen);

    bool play();

private:
    static bool userWantToExit(const ALLEGRO_EVENT& event);

    static bool userWantToQuit(const ALLEGRO_EVENT& event);

    static void movement(Tank& myTank, Map& map);
    void drawStatusPlaceholder();
    void control(Map& map);

    void drawEndOfGame(const std::string& text);

    Screen& screen_;
    ALLEGRO_BITMAP* buffer_{nullptr};
    bool gameOver_{false};
};
