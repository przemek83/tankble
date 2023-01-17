#pragma once

#include <set>
#include <string>

class Tank;
class Map;
class Screen;
class Input;
enum class InputAction : unsigned char;

class Game
{
public:
    explicit Game(Screen& screen);

    bool play();

private:
    static void movement(Tank& myTank, Map& map,
                         const std::set<InputAction>& actions);
    void drawStatusPlaceholder();
    static void control(Map& map);
    void drawEndOfGame(const std::string& text);
    static bool isPlayerMoving(const std::set<InputAction>& actions);
    bool isGameEnding(Map& map);

    Screen& screen_;
};
