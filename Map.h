#pragma once

#include <list>
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

    std::list<Tank> loadMap(std::iostream& stream);

    bool canDrive(Point point) const;
    bool canFly(Point point) const;

    std::pair<bool, ResourceType> takePowerUp(Point point);

    void drawBackground(const Screen& screen);
    void drawForeground(const Screen& screen);

    bool isBaseDestroyed() const;

    void hit(Point point, unsigned int power);

private:
    inline const std::unique_ptr<Tile>& getTile(Point point) const
    {
        return board_[point.y][point.x];
    }

    inline std::unique_ptr<Tile>& getTile(Point point)
    {
        return board_[point.y][point.x];
    }

    static Point screenPointToTile(Point location);
    static Point tileToScreenPoint(Point point);

    std::vector<std::vector<std::unique_ptr<Tile>>> board_{};

    bool baseDestroyed_{false};

    std::unique_ptr<Tile> plainTile_;
    const unsigned int mapDimension_;
};
