#pragma once

#include <memory>
#include <vector>

#include "ResourceType.h"
#include "map/Tile.h"

class Tank;
class Screen;

class Map
{
public:
    explicit Map(unsigned int mapDimension);

    std::vector<Tank> loadMap(std::fstream stream);

    bool canDrive(Point point) const;
    bool canFly(Point point) const;

    bool isValid(int x, int y) const;
    std::pair<bool, ResourceType> takePowerUp(Point point);

    void drawBackground(const Screen& screen);
    void drawForeground(const Screen& screen);

    bool isPlayerDestroyed() const;

    void destroyItem(Point point, unsigned int power);

    static Point screenPointToTile(Point location);

private:
    inline const std::unique_ptr<Tile>& getTile(Point point) const
    {
        return board_[point.y][point.x];
    }

    inline std::unique_ptr<Tile>& getTile(Point point)
    {
        return board_[point.y][point.x];
    }

    std::vector<std::vector<std::unique_ptr<Tile>>> board_{};

    bool playerDestroyed_{false};

    std::unique_ptr<Tile> plainTile_;
    const unsigned int mapDimension_;
};
