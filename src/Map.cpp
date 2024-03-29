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

Map::Map(unsigned int mapDimension)
    : plainTile_{std::make_unique<Plain>(Point{0, 0})},
      mapDimension_(mapDimension)
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
    for (unsigned int y = 0; y < mapDimension_; y++)
        for (unsigned int x = 0; x < mapDimension_; x++)
        {
            stream >> std::noskipws >> sign;

            while ((sign < '0' || sign >= '7') && sign != 'T' && sign != 'E' &&
                   sign != 'M' && sign != 'S' && sign != 'L' && sign != 'A')
            {
                stream >> std::noskipws >> sign;
                if (sign == EOF)
                    break;
            }

            const Point point{x * Config::getInstance().getTileSize(),
                              y * Config::getInstance().getTileSize()};

            auto& tile{getTile({x, y})};
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
    return getTile(screenPointToTile(point))->canDrive();
}

std::pair<bool, ResourceType> Map::takePowerUp(Point point)
{
    auto& tile{getTile(screenPointToTile(point))};
    if (!tile->isPowerUp())
        return {false, ResourceType::PLAIN};
    const ResourceType type{tile->getResourceType()};
    tile = std::make_unique<Plain>(tile->getLocation());
    return {true, type};
}

bool Map::canFly(Point point) const
{
    return getTile(screenPointToTile(point))->canFly();
}

void Map::hit(Point point, unsigned int power)
{
    auto [x, y]{screenPointToTile(point)};
    auto& tile{getTile({x, y})};
    if (!canFly(point) && tile->hit(power))
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
    const unsigned int tileSize{Config::getInstance().getTileSize()};
    const Point leftUpper{pointToShift};
    const Point leftLower{leftUpper.x, leftUpper.y + tileSize - 1};
    const Point rightUpper{leftUpper.x + tileSize - 1, leftUpper.y};
    const Point rightLower{leftUpper.x + tileSize - 1,
                           leftUpper.y + tileSize - 1};
    switch (direction)
    {
        case Direction::UP:
        case Direction::DOWN:
        {
            if (!canDrive(leftUpper) || !canDrive(leftLower))
                shiftRight(pointToShift, tileSize);

            if (!canDrive(rightUpper) || !canDrive(rightLower))
                shiftLeft(pointToShift, tileSize);
            break;
        }

        case Direction::LEFT:
        case Direction::RIGHT:
        {
            if (!canDrive(leftUpper) || !canDrive(rightUpper))
                shiftDown(pointToShift, tileSize);

            if (!canDrive(leftLower) || !canDrive(rightLower))
                shiftUp(pointToShift, tileSize);
            break;
        }
    }
}

void Map::tagAreaAsChanged(Point leftUpper, Point rightLower)
{
    const unsigned int tileSize{Config::getInstance().getTileSize()};
    Point point{screenPointToTile(leftUpper)};
    if (PointUtils::isValidPoint(leftUpper))
        changedTiles_[point.x][point.y] = true;

    point = screenPointToTile({leftUpper.x, leftUpper.y + tileSize});
    if (PointUtils::isValidPoint({leftUpper.x, leftUpper.y + tileSize}))
        changedTiles_[point.x][point.y] = true;

    point = screenPointToTile(rightLower);
    if (PointUtils::isValidPoint(rightLower))
        changedTiles_[point.x][point.y] = true;

    point = screenPointToTile({rightLower.x, rightLower.y - tileSize});
    if (PointUtils::isValidPoint({rightLower.x, rightLower.y - tileSize}))
        changedTiles_[point.x][point.y] = true;
}

Point Map::screenPointToTile(Point location)
{
    return {location.x / Config::getInstance().getTileSize(),
            location.y / Config::getInstance().getTileSize()};
}

Point Map::tileToScreenPoint(Point point)
{
    return {point.x * Config::getInstance().getTileSize(),
            point.y * Config::getInstance().getTileSize()};
}

void Map::shiftRight(Point& point, unsigned int tileSize)
{
    point.x = (point.x / tileSize + 1) * tileSize;
}

void Map::shiftLeft(Point& point, unsigned int tileSize)
{
    point.x = (point.x / tileSize) * tileSize;
}

void Map::shiftUp(Point& point, unsigned int tileSize)
{
    point.y = (point.y / tileSize) * tileSize;
}

void Map::shiftDown(Point& point, unsigned int tileSize)
{
    point.y = (point.y / tileSize + 1) * tileSize;
}

void Map::drawBackground(const Screen& screen)
{
    for (unsigned int x = 0; x < mapDimension_; x++)
        for (unsigned int y = 0; y < mapDimension_; y++)
        {
            if (!changedTiles_[x][y])
                continue;

            const auto& tile{getTile({x, y})};
            if (tile->isPartOfBackground())
            {
                tile->draw(screen);
                changedTiles_[x][y] = false;
            }

            else
            {
                plainTile_->setLocation(tileToScreenPoint({x, y}));
                plainTile_->draw(screen);
            }
        }
}

void Map::drawForeground(const Screen& screen)
{
    for (unsigned int x = 0; x < mapDimension_; x++)
        for (unsigned int y = 0; y < mapDimension_; y++)
        {
            if (!changedTiles_[x][y])
                continue;

            const auto& tile{getTile({x, y})};
            if (!tile->isPartOfBackground())
            {
                tile->draw(screen);
                changedTiles_[x][y] = false;
            }
        }
}

bool Map::isBaseDestroyed() const { return baseDestroyed_; }
