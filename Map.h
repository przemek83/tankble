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

    bool canDrive(unsigned int x, unsigned int y) const;
    bool canFly(unsigned int x, unsigned int y) const;

    bool isValid(int x, int y);
    std::pair<bool, ResourceType> takePowerUp(unsigned int x, unsigned int y);

    void drawBackground(const Screen& screen);
    void drawForeground(const Screen& screen);

    bool isPlayerDestroyed() const;

    void destroyItem(unsigned int x, unsigned int y, unsigned int power);

private:
    static void drawMapItem(const Screen& screen, ResourceType resourceType,
                            unsigned int x, unsigned int y);

    inline const std::unique_ptr<Tile>& getTile(unsigned int x,
                                                unsigned int y) const
    {
        return board_[y][x];
    }

    inline std::unique_ptr<Tile>& getTile(unsigned int x, unsigned int y)
    {
        return board_[y][x];
    }

    std::vector<std::vector<std::unique_ptr<Tile>>> board_{};

    bool playerDestroyed_{false};
};
