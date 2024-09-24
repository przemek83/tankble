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
    explicit Map(int mapDimension);

    std::list<Tank> loadMap(std::iostream& stream);

    bool canDrive(Point point) const;
    bool canFly(Point point) const;

    std::pair<bool, ResourceType> takePowerUp(Point point);

    void drawBackground(const Screen& screen);
    void drawForeground(const Screen& screen);

    bool isBaseDestroyed() const;

    void hit(Point point, int power);

    void shift(Point& pointToShift, Direction direction) const;

    void tagAreaAsChanged(Point leftUpper, Point rightLower);

private:
    struct TilePosition
    {
        std::size_t x_;
        std::size_t y_;
    };

    std::unique_ptr<Tile>& getTile(Point point)
    {
        return board_[static_cast<std::size_t>(point.y_)]
                     [static_cast<std::size_t>(point.x_)];
    }

    const std::unique_ptr<Tile>& getTileUsingPosition(
        TilePosition position) const
    {
        return board_[position.y_][position.x_];
    }

    std::unique_ptr<Tile>& getTileUsingPosition(TilePosition position)
    {
        return board_[position.y_][position.x_];
    }

    static TilePosition screenPointToTilePosition(Point point);
    static Point tilePositionToScreenPoint(TilePosition position);

    void createTile(char sign, std::list<Tank>& tanks, TilePosition position);

    static void shiftRight(Point& point, int tileSize);
    static void shiftLeft(Point& point, int tileSize);
    static void shiftUp(Point& point, int tileSize);
    static void shiftDown(Point& point, int tileSize);

    bool isTileSign(char sign) const;

    std::vector<std::vector<std::unique_ptr<Tile>>> board_{};

    std::vector<std::vector<bool>> changedTiles_{};

    bool baseDestroyed_{false};

    std::unique_ptr<Tile> plainTile_;
    const std::size_t mapDimension_;
};
