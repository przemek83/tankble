#pragma once

#include <list>
#include <random>
#include <set>
#include <string>

#include "Direction.h"
#include "Status.h"

struct Point;
class Tank;
class Map;
class Screen;
class Input;
enum class InputAction : unsigned char;
class Bullet;
enum class Level : unsigned char;

class Game
{
public:
    explicit Game(Screen& screen);

    bool play(Level level);

private:
    static void movement(Tank& tank, Map& map, Direction direction);
    void control(Map& map, std::list<Tank>& tanks, std::list<Bullet>& bullets);
    bool isGameEnding(const Map& map, const std::list<Tank>& tanks);
    void moveBullets(std::list<Bullet>& bullets, std::list<Tank>& tanks,
                     Map& map);
    static std::list<Tank>::iterator hitTank(const Bullet& bullet,
                                             std::list<Tank>& tanks);

    void drawTanks(const std::list<Tank>& tanks) const;
    void drawEndOfGame(const std::string& text) const;
    void drawBullets(const std::list<Bullet>& bullets) const;
    void draw(const std::list<Bullet>& bullets, const std::list<Tank>& tanks,
              Map& map);
    static void setPower(Tank& tank, Map& map);

    static std::pair<bool, Direction> inputActionsToDirection(
        const std::set<InputAction>& actions);

    static const Tank& getPlayerTank(const std::list<Tank>& tanks);

    Status status_;
    std::mt19937 randomGenerator_;
    Screen& screen_;
    bool playerDestroyed_{false};
    std::uniform_int_distribution<> distribution_{
        std::uniform_int_distribution<>(0, 7)};
};
