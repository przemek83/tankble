#pragma once

#include <memory>
#include <vector>

#include "ResourceType.h"
#include "map/Tile.h"

class Tank;
class Resources;
class Screen;

class Map
{
public:
    explicit Map(const Resources& resources);

    std::vector<Tank> loadMap();

    bool canDrive(unsigned int j, unsigned int i);
    bool canFly(unsigned int j, unsigned int i) const;

    bool isValid(int, int);
    void setPower(Tank& vehicle);

    void drawBackground(const Screen& screen);
    void drawForeground(Screen& screen);
    void drawPowers(Screen& screen);

    bool isPlayerDestroyed() const;

    void destroyItem(unsigned int j, unsigned int i, unsigned int power);

private:
    void drawMapItem(const Screen& screen, ResourceType resourceType, int x,
                     int y);

    const Resources& resources_;
    std::vector<std::vector<std::unique_ptr<Tile>>> board_{};

    bool playerDestroyed_{false};
};
