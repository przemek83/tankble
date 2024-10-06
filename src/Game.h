#pragma once

#include <list>
#include <random>
#include <set>
#include <string>

#include "Bullet.h"
#include "Direction.h"
#include "Map.h"
#include "Status.h"
#include "Tank.h"

struct Point;
class Display;
enum class InputAction : char;
enum class Level : char;
class Input;

class Game
{
public:
    explicit Game(Display& display);

    void init(std::iostream& level);

    bool play(Input& input);

private:
    void movement(Tank& tank, Direction direction);
    void control();
    bool isGameEnding() const;
    void moveBullets();
    std::list<Tank>::iterator hitTank(const Bullet& bullet);

    void drawTanks() const;
    void drawEndOfGame(const std::string& text) const;
    void drawBullets() const;
    void draw();
    void setPower(Tank& tank);

    static std::pair<bool, Direction> inputActionsToDirection(
        const std::set<InputAction>& actions);

    const Tank& getPlayerTank();

    Status status_;
    std::mt19937 randomGenerator_;
    Display& display_;
    bool playerDestroyed_{false};
    std::uniform_int_distribution<> distribution_{
        std::uniform_int_distribution<>(0, 7)};

    std::list<Tank> tanks_;
    Map map_;
    std::list<Bullet> bullets_;
};
