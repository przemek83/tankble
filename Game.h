#pragma once

#include <string>

class Tank;
class Map;
class Screen;

class Game
{
public:
    explicit Game(Screen& screen);

    bool play();

private:
    static void movement(Tank& myTank, Map& map);
    void drawStatusPlaceholder();
    void control(Map& map);

    void drawEndOfGame(const std::string& text);

    Screen& screen_;
    bool gameOver_{false};
};
