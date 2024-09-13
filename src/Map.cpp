#include "Map.h"

#include <iostream>

#include "Config.h"
#include "PointUtils.h"
#include "Screen.h"
#include "Tank.h"
#include "map/Base.h"
#include "map/Brick.h"
#include "map/Ice.h"
#include "map/LifeUp.h"
#include "map/Plain.h"
#include "map/Plant.h"
#include "map/ShieldUp.h"
#include "map/SpeedUp.h"
#include "map/Steel.h"
#include "map/TierUp.h"
#include "map/Water.h"

Map::Map(int mapDimension)
    : plainTile_{std::make_unique<Plain>(Point{0, 0})},
      mapDimension_{static_cast<std::size_t>(mapDimension)}
{
    board_.resize(mapDimension_);
    for (auto& item : board_)
        item.resize(mapDimension_);

    changedTiles_.resize(mapDimension_);
    for (auto& item : changedTiles_)
        item.resize(mapDimension_, true);
}

// 0 - plain
// 1 - brick
// 2 - water
// 3 - plant
// 4 - ice
// 5 - steel
// 6 - HQ
// M - my/player tank
// E - enemy tank
// S - speed up
// L - tier up
// A - shield up
// T - life up

std::list<Tank> Map::loadMap(std::iostream& stream)
{
    char sign{};
    std::list<Tank> tanks;
    for (std::size_t y = 0; y < mapDimension_; ++y)
        for (std::size_t x = 0; x < mapDimension_; ++x)
        {
            stream >> std::noskipws >> sign;

            while (((sign < '0') || (sign >= '7')) && (sign != 'T') &&
                   (sign != 'E') && (sign != 'M') && (sign != 'S') &&
                   (sign != 'L') && (sign != 'A'))
            {
                stream >> std::noskipws >> sign;
                if (sign == EOF)
                    break;
            }

            const Point point{
                static_cast<int>(x) * Config::getInstance().getTileSize(),
                static_cast<int>(y) * Config::getInstance().getTileSize()};

            auto& tile{getTileUsingPosition({x, y})};
            switch (sign)
            {
                case '1':
                    tile = std::make_unique<Brick>(point);
                    break;
                case '2':
                    tile = std::make_unique<Water>(point);
                    break;
                case '3':
                    tile = std::make_unique<Plant>(point);
                    break;
                case '4':
                    tile = std::make_unique<Ice>(point);
                    break;
                case '5':
                    tile = std::make_unique<Steel>(point);
                    break;
                case '6':
                    tile = std::make_unique<Base>(point);
                    break;
                case 'M':
                    tile = std::make_unique<Plain>(point);
                    tanks.emplace_back(TankType::PLAYER_TIER_1, point);
                    break;
                case 'E':
                    tile = std::make_unique<Plain>(point);
                    tanks.emplace_back(TankType::ENEMY_TIER_1, point);
                    break;
                case 'A':
                    tile = std::make_unique<ShieldUp>(point);
                    break;
                case 'S':
                    tile = std::make_unique<SpeedUp>(point);
                    break;
                case 'L':
                    tile = std::make_unique<TierUp>(point);
                    break;
                case 'T':
                    tile = std::make_unique<LifeUp>(point);
                    break;
                default:
                    tile = std::make_unique<Plain>(point);
            }
        }

    return tanks;
}

bool Map::canDrive(Point point) const
{
    return getTileUsingPosition(screenPointToTilePosition(point))->canDrive();
}

std::pair<bool, ResourceType> Map::takePowerUp(Point point)
{
    auto& tile{getTileUsingPosition(screenPointToTilePosition(point))};
    if (!tile->isPowerUp())
        return {false, ResourceType::PLAIN};
    const ResourceType type{tile->getResourceType()};
    tile = std::make_unique<Plain>(tile->getLocation());
    return {true, type};
}

bool Map::canFly(Point point) const
{
    return getTileUsingPosition(screenPointToTilePosition(point))->canFly();
}

void Map::hit(Point point, int power)
{
    auto [x, y]{screenPointToTilePosition(point)};
    auto& tile{getTileUsingPosition({x, y})};
    if ((!canFly(point)) && tile->hit(power))
    {
        const bool baseDestroyed{tile->getResourceType() == ResourceType::BASE};
        tile = std::make_unique<Plain>(tile->getLocation());
        if (baseDestroyed)
            baseDestroyed_ = true;
        changedTiles_[x][y] = true;
    }
}

void Map::shift(Point& pointToShift, Direction direction) const
{
    const int tileSize{Config::getInstance().getTileSize()};
    const Point leftUpper{pointToShift};
    const Point leftLower{leftUpper.x_, (leftUpper.y_ + tileSize) - 1};
    const Point rightUpper{(leftUpper.x_ + tileSize) - 1, leftUpper.y_};
    const Point rightLower{(leftUpper.x_ + tileSize) - 1,
                           (leftUpper.y_ + tileSize) - 1};
    switch (direction)
    {
        case Direction::UP:
        case Direction::DOWN:
        {
            if ((!canDrive(leftUpper)) || (!canDrive(leftLower)))
                shiftRight(pointToShift, tileSize);

            if ((!canDrive(rightUpper)) || (!canDrive(rightLower)))
                shiftLeft(pointToShift, tileSize);
            break;
        }

        case Direction::LEFT:
        case Direction::RIGHT:
        {
            if ((!canDrive(leftUpper)) || (!canDrive(rightUpper)))
                shiftDown(pointToShift, tileSize);

            if ((!canDrive(leftLower)) || (!canDrive(rightLower)))
                shiftUp(pointToShift, tileSize);
            break;
        }

        default:
            break;
    }
}

void Map::tagAreaAsChanged(Point leftUpper, Point rightLower)
{
    const int tileSize{Config::getInstance().getTileSize()};
    TilePosition position{screenPointToTilePosition(leftUpper)};
    if (point_utils::isValidPoint(leftUpper))
        changedTiles_[position.x_][position.y_] = true;

    position =
        screenPointToTilePosition({leftUpper.x_, leftUpper.y_ + tileSize});
    if (point_utils::isValidPoint({leftUpper.x_, leftUpper.y_ + tileSize}))
        changedTiles_[position.x_][position.y_] = true;

    position = screenPointToTilePosition(rightLower);
    if (point_utils::isValidPoint(rightLower))
        changedTiles_[position.x_][position.y_] = true;

    position = screenPointToTilePosition(
        Point{rightLower.x_, rightLower.y_ - tileSize});
    if (point_utils::isValidPoint({rightLower.x_, rightLower.y_ - tileSize}))
        changedTiles_[position.x_][position.y_] = true;
}

Map::TilePosition Map::screenPointToTilePosition(Point point)
{
    const int tileSize{Config::getInstance().getTileSize()};
    std::size_t x{static_cast<std::size_t>(point.x_ / tileSize)};
    std::size_t y{static_cast<std::size_t>(point.y_ / tileSize)};
    return {x, y};
}

Point Map::tilePositionToScreenPoint(TilePosition position)
{
    const int tileSize{Config::getInstance().getTileSize()};
    return {static_cast<int>(position.x_) * tileSize,
            static_cast<int>(position.y_) * tileSize};
}

void Map::shiftRight(Point& point, int tileSize)
{
    point.x_ = ((point.x_ / tileSize) + 1) * tileSize;
}

void Map::shiftLeft(Point& point, int tileSize)
{
    point.x_ = (point.x_ / tileSize) * tileSize;
}

void Map::shiftUp(Point& point, int tileSize)
{
    point.y_ = (point.y_ / tileSize) * tileSize;
}

void Map::shiftDown(Point& point, int tileSize)
{
    point.y_ = (point.y_ / tileSize + 1) * tileSize;
}

void Map::drawBackground(const Screen& screen)
{
    for (std::size_t x = 0; x < mapDimension_; ++x)
        for (std::size_t y = 0; y < mapDimension_; ++y)
        {
            if (!changedTiles_[x][y])
                continue;

            const auto& tile{getTileUsingPosition({x, y})};
            if (tile->isPartOfBackground())
            {
                tile->draw(screen);
                changedTiles_[x][y] = false;
            }

            else
            {
                plainTile_->setLocation(tilePositionToScreenPoint({x, y}));
                plainTile_->draw(screen);
            }
        }
}

void Map::drawForeground(const Screen& screen)
{
    for (std::size_t x = 0; x < mapDimension_; ++x)
        for (std::size_t y = 0; y < mapDimension_; ++y)
        {
            if (!changedTiles_[x][y])
                continue;

            const auto& tile{getTileUsingPosition({x, y})};
            if (!tile->isPartOfBackground())
            {
                tile->draw(screen);
                changedTiles_[x][y] = false;
            }
        }
}

bool Map::isBaseDestroyed() const { return baseDestroyed_; }
