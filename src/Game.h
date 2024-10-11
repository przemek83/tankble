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

class Game
{
public:
    Game(std::list<Tank>& tanks, Map& map);

    void moveBullets();

    void movePlayerTank(const std::set<InputAction>& actions);

    void moveEnemyTanks();

    bool isGameEnding(Display& display) const;

    void draw(const Display& display);

private:
    void movement(Tank& tank, Direction direction);
    std::list<Tank>::iterator getImpactedTank(const Bullet& bullet);

    void drawTanks(const Display& display) const;
    void drawEndOfGame(Display& display, const std::string& text) const;
    void drawBullets(const Display& display) const;

    static std::pair<bool, Direction> inputActionsToDirection(
        const std::set<InputAction>& actions);

    Tank& getPlayerTank();

    static bool containsAction(const std::set<InputAction>& actions,
                               InputAction action);

    void tagAreaAsChanged(const Drawable& object, int size);

    bool canDrive(Point point, Direction direction) const;

    Direction getEnemyTankDirection(const Tank& tank);

    void hitTank(const std::list<Tank>::iterator& tankIter, int power);

    Status status_;
    std::mt19937 randomGenerator_;
    bool playerDestroyed_{false};
    std::uniform_int_distribution<> distribution_{
        std::uniform_int_distribution<>(0, 7)};

    std::list<Tank>& tanks_;
    Map& map_;
    std::list<Bullet> bullets_;
};
