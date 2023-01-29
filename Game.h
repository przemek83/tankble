#pragma once

#include <list>
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
    void control(Map& map, std::vector<Tank>& tanks,
                 std::list<Bullet>& bullets);
    bool isGameEnding(const Map& map, const std::vector<Tank>& tanks);
    void moveBullets(std::list<Bullet>& bullets, std::vector<Tank>& tanks,
                     Map& map);
    static std::vector<Tank>::iterator hitTank(const Bullet& bullet,
                                               std::vector<Tank>& tanks);

    void drawStatusPlaceholder();
    void drawTanks(const std::vector<Tank>& tanks);
    void drawEndOfGame(const std::string& text);
    void drawBullets(const std::list<Bullet>& bullets);
    void draw(const std::list<Bullet>& bullets, const std::vector<Tank>& tanks,
              Map& map);
    static void setPower(Tank& tank, Map& map);

    static std::pair<bool, Direction> inputActionsToDirection(
        const std::set<InputAction>& actions);

    static std::vector<Point> getMovingPoints(Point leftUpperCorner,
                                              Direction direction);
    static bool tankIsInMap(const Map& map, int newX, int newY);
    static void shiftIfNeeded(Point& point, const Map& map,
                              Direction direction);

    Screen& screen_;
    bool playerDestroyed_{false};
};
