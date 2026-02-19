#pragma once

#include <list>
#include <memory>
#include <vector>

#include "Direction.h"
#include "ResourceType.h"
#include "map/Plain.h"
#include "map/Tile.h"

class Tank;
class Display;

class Map
{
public:
    explicit Map(int mapDimension);

    std::list<Tank> loadMap(std::iostream& stream);

    bool canDrive(Point point) const;
    bool canFly(Point point) const;

    std::pair<bool, ResourceType> takePowerUp(Point point);

    void drawBackground(const Display& display);
    void drawForeground(const Display& display);

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

    const std::unique_ptr<Tile>& getTileUsingPosition(
        TilePosition position) const;

    std::unique_ptr<Tile>& getTileUsingPosition(TilePosition position);

    static TilePosition screenPointToTilePosition(Point point);
    static Point tilePositionToScreenPoint(TilePosition position);

    void createTile(char sign, std::list<Tank>& tanks, TilePosition position);

    static void shiftRight(Point& point, int tileSize);
    static void shiftLeft(Point& point, int tileSize);
    static void shiftUp(Point& point, int tileSize);
    static void shiftDown(Point& point, int tileSize);

    static bool isValidSign(char sign);

    void drawBackgroundTile(const Display& display, TilePosition position);
    void drawForegroundTile(const Display& display, TilePosition position);

    std::vector<std::vector<std::unique_ptr<Tile>>> board_;

    const unsigned char tileNotChanged_{0};
    const unsigned char tileChanged_{1};

    std::vector<std::vector<unsigned char>> changedTiles_;

    bool baseDestroyed_{false};

    std::unique_ptr<Tile> plainTile_{std::make_unique<Plain>(Point{0, 0})};
    const std::size_t mapDimension_;
};
