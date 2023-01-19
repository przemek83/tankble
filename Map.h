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
    Map();

    std::vector<Tank> loadMap(std::fstream stream);

    bool canDrive(unsigned int j, unsigned int i) const;
    bool canFly(unsigned int j, unsigned int i) const;

    bool isValid(int x, int y);
    void setPower(Tank& vehicle);

    void drawBackground(const Screen& screen);
    void drawForeground(const Screen& screen);

    bool isPlayerDestroyed() const;

    void destroyItem(unsigned int j, unsigned int i, unsigned int power);

private:
    void drawMapItem(const Screen& screen, ResourceType resourceType, int x,
                     int y);

    std::vector<std::vector<std::unique_ptr<Tile>>> board_{};

    bool playerDestroyed_{false};
};
