#pragma once

#include <list>
#include <random>
#include <set>
#include <string>
#include <vector>

#include "Direction.h"

class Point;
class Tank;
class Map;
class Screen;
class Input;
enum class InputAction : unsigned char;
class Bullet;

class Game
{
public:
    explicit Game(Screen& screen);

    bool play();

private:
    static void movement(Tank& tank, Map& map, Direction direction);
    void control(Map& map, std::list<Tank>& tanks, std::list<Bullet>& bullets);
    bool isGameEnding(const Map& map, const std::list<Tank>& tanks);
    void moveBullets(std::list<Bullet>& bullets, std::list<Tank>& tanks,
                     Map& map);
    static std::list<Tank>::iterator hitTank(const Bullet& bullet,
                                             std::list<Tank>& tanks);

    void drawStatusPlaceholder();
    void drawTanks(const std::list<Tank>& tanks);
    void drawEndOfGame(const std::string& text);
    void drawBullets(const std::list<Bullet>& bullets);
    void draw(const std::list<Bullet>& bullets, const std::list<Tank>& tanks,
              Map& map);
    static void setPower(Tank& tank, Map& map);

    static std::pair<bool, Direction> inputActionsToDirection(
        const std::set<InputAction>& actions);

    static std::vector<Point> getMovingPoints(Point leftUpperCorner,
                                              Direction direction);

    static void shiftIfNeeded(Point& leftUpper, const Map& map,
                              Direction direction);
    static void shiftRight(Point& point, unsigned int tileSize);
    static void shiftLeft(Point& point, unsigned int tileSize);
    static void shiftUp(Point& point, unsigned int tileSize);
    static void shiftDown(Point& point, unsigned int tileSize);

    std::mt19937 randomGenerator_;
    Screen& screen_;
    bool playerDestroyed_{false};
};
