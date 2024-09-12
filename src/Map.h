#pragma once

#include <list>
#include <memory>
#include <vector>

#include "Direction.h"
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

    void shift(Point& pointToShift, Direction direction) const;

    void tagAreaAsChanged(Point leftUpper, Point rightLower);

private:
    const std::unique_ptr<Tile>& getTile(Point point) const
    {
        return board_[point.y][point.x];
    }

    std::unique_ptr<Tile>& getTile(Point point)
    {
        return board_[point.y][point.x];
    }

    static Point screenPointToTile(Point location);
    static Point tileToScreenPoint(Point point);

    static void shiftRight(Point& point, unsigned int tileSize);
    static void shiftLeft(Point& point, unsigned int tileSize);
    static void shiftUp(Point& point, unsigned int tileSize);
    static void shiftDown(Point& point, unsigned int tileSize);

    std::vector<std::vector<std::unique_ptr<Tile>>> board_{};

    std::vector<std::vector<bool>> changedTiles_{};

    bool baseDestroyed_{false};

    std::unique_ptr<Tile> plainTile_;
    const unsigned int mapDimension_;
};
