#pragma once

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
    static void control(Map& map, std::vector<Tank>& tanks,
                        std::vector<Bullet>& bullets);
    static bool isPlayerMoving(const std::set<InputAction>& actions);
    bool isGameEnding(const Map& map, const std::vector<Tank>& tanks);
    void moveBullets(std::vector<Bullet>& bullets, std::vector<Tank>& tanks,
                     Map& map);
    int isTank(const Bullet& bullet, std::vector<Tank>& tanks);
    bool isBulletValid(int x, int y);

    void drawStatusPlaceholder();
    static void drawTanks(const Screen& screen, const std::vector<Tank>& tanks);
    void drawEndOfGame(const std::string& text);
    void drawBullets(const Screen& screen, std::vector<Bullet>& bullets);

    Screen& screen_;
    bool playerDestroyed_{false};
};
