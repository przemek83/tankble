#pragma once

#include <memory>
#include <vector>

#include "ResourceType.h"

class Tank;
class Bullet;
class Tile;
class Resources;
class Screen;

class Map
{
public:
    explicit Map(const Resources& resources);
    ~Map();

    Map& operator=(const Map& other) = delete;
    Map(const Map& other) = delete;

    Map& operator=(Map&& other) = delete;
    Map(Map&& other) = delete;

    bool canDrive(unsigned int j, unsigned int i);
    bool isValid(int, int);
    void addBullet(std::unique_ptr<Bullet> bullet);
    void moveBullet();
    void setPower(Tank& vehicle);

    void drawBackground(const Screen& screen);
    void drawForeground(Screen& screen);
    void drawPowers(Screen& screen);
    void drawVehicles(const Screen& screen);
    void drawBullets(const Screen& screen);

    std::vector<Tank>& getTanks();

    bool isPlayerDestroyed() const;

private:
    bool isBulletValid(int x, int y);
    bool canFly(unsigned int j, unsigned int i);
    void destroyItem(unsigned int j, unsigned int i, unsigned int power);
    int isTank(const std::unique_ptr<Bullet>& bullet);
    void loadMap();
    void drawMapItem(const Screen& screen, ResourceType resourceType, int x,
                     int y);

    const Resources& resources_;
    std::vector<Tank> tanks_;
    std::vector<std::unique_ptr<Bullet>> bullets_;
    std::vector<std::vector<std::unique_ptr<Tile>>> board_{};

    bool playerDestroyed_{false};
};
