#pragma once

#include <list>
#include <set>
#include <string>
#include <vector>

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
    static void movement(Tank& myTank, Map& map,
                         const std::set<InputAction>& actions);
    void control(Map& map, std::vector<Tank>& tanks,
                 std::list<Bullet>& bullets);
    static bool isPlayerMoving(const std::set<InputAction>& actions);
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

    Screen& screen_;
    bool playerDestroyed_{false};
};
