#pragma once

#include <memory>
#include <vector>

#include "Bullet.h"
#include "ResourceType.h"
#include "map/Tile.h"

class Tank;
class Resources;
class Screen;

class Map
{
public:
    explicit Map(const Resources& resources);

    bool canDrive(unsigned int j, unsigned int i);
    bool isValid(int, int);
    void addBullet(Bullet bullet);
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
    int isTank(const Bullet& bullet);
    void loadMap();
    void drawMapItem(const Screen& screen, ResourceType resourceType, int x,
                     int y);

    const Resources& resources_;
    std::vector<Tank> tanks_;
    std::vector<Bullet> bullets_;
    std::vector<std::vector<std::unique_ptr<Tile>>> board_{};

    bool playerDestroyed_{false};
};
