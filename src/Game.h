#pragma once

#include <list>
#include <random>
#include <set>
#include <string>

#include "Direction.h"
#include "Map.h"
#include "Status.h"
#include "Tank.h"

struct Point;
class Display;
enum class InputAction : char;
class Bullet;
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
    void control(std::list<Bullet>& bullets);
    bool isGameEnding() const;
    void moveBullets(std::list<Bullet>& bullets);
    std::list<Tank>::iterator hitTank(const Bullet& bullet);

    void drawTanks() const;
    void drawEndOfGame(const std::string& text) const;
    void drawBullets(const std::list<Bullet>& bullets) const;
    void draw(const std::list<Bullet>& bullets);
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
};
