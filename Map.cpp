#include "Map.h"

#include <fstream>

#include "Config.h"
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

Map::Map() : plainTile_{std::make_unique<Plain>(Point{0, 0})}
{
    board_.resize(Config::mapSize);
    for (auto& item : board_)
        item.resize(Config::mapSize);
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

std::vector<Tank> Map::loadMap(std::fstream stream)
{
    char sign{};
    std::vector<Tank> tanks;
    for (unsigned int y = 0; y < Config::mapSize; y++)
        for (unsigned int x = 0; x < Config::mapSize; x++)
        {
            stream >> std::noskipws >> sign;

            while ((sign < '0' || sign >= '7') && sign != 'T' && sign != 'E' &&
                   sign != 'M' && sign != 'S' && sign != 'L' && sign != 'A')
            {
                stream >> std::noskipws >> sign;
                if (sign == EOF)
                    break;
            }

            const Point point{x * Config::elementSize, y * Config::elementSize};

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

bool Map::canDrive(unsigned int x, unsigned int y) const
{
    return getTile({x, y})->canDrive();
}

bool Map::isValid(int x, int y)
{
    constexpr int maxCoordinate{
        static_cast<int>((Config::mapSize - 1) * Config::elementSize)};
    return x >= 0 && x < maxCoordinate && y >= 0 && y < maxCoordinate;
}

std::pair<bool, ResourceType> Map::takePowerUp(unsigned int x, unsigned int y)
{
    auto& tile{getTile({x, y})};
    if (!tile->isPowerUp())
        return {false, ResourceType::PLAIN};
    const ResourceType type{tile->getResourceType()};
    tile = std::make_unique<Plain>(
        Point{x * Config::elementSize, y * Config::elementSize});
    return {true, type};
}

bool Map::canFly(Point point) const
{
    return getTile(screenPointToTile(point))->canFly();
}

void Map::destroyItem(Point point, unsigned int power)
{
    auto& tile{getTile(screenPointToTile(point))};
    if (tile->destroy(power))
    {
        const bool baseDestroyed{tile->getResourceType() == ResourceType::BASE};
        tile = std::make_unique<Plain>(tile->getLocation());
        if (baseDestroyed)
            playerDestroyed_ = true;
    }
}

Point Map::screenPointToTile(Point location)
{
    return {location.x / Config::elementSize, location.y / Config::elementSize};
}

void Map::drawBackground(const Screen& screen)
{
    for (unsigned int x = 0; x < Config::mapSize; x++)
        for (unsigned int y = 0; y < Config::mapSize; y++)
        {
            const auto& tile{getTile({x, y})};
            if (tile->isPartOfBackground())
                tile->draw(screen);
            else
            {
                plainTile_->setX(x * Config::elementSize);
                plainTile_->setY(y * Config::elementSize);
                plainTile_->draw(screen);
            }
        }
}

void Map::drawForeground(const Screen& screen)
{
    for (unsigned int x = 0; x < Config::mapSize; x++)
        for (unsigned int y = 0; y < Config::mapSize; y++)
        {
            const auto& tile{getTile({x, y})};
            if (!tile->isPartOfBackground())
                tile->draw(screen);
        }
}

bool Map::isPlayerDestroyed() const { return playerDestroyed_; }
