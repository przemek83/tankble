#include "Map.h"

#include <fstream>
#include <iostream>

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

Map::Map()
{
    board_.resize(Config::mapSize);
    for (auto& item : board_)
        item.resize(Config::mapSize);
}

/*
0 - trawa
1 - cegla
2 - woda
3 - zielsko
4 - lod
5 - stal
6 - orzel
7 -
M - czolg gracza
E - czolg przeciwnika
S - speed up
L - level up
A - armor up
T - tank up
*/
std::vector<Tank> Map::loadMap(std::fstream stream)
{
    const int on = clock();

    char sign{};
    std::vector<Tank> tanks;
    for (unsigned int y = 0; y < Config::mapSize; y++)
        for (unsigned int x = 0; x < Config::mapSize; x++)
        {
            stream >> std::noskipws >> sign;

            while ((sign < '0' || sign >= '8') && sign != 'T' && sign != 'E' &&
                   sign != 'M' && sign != 'S' && sign != 'L' && sign != 'A')
            {
                stream >> std::noskipws >> sign;
                if (sign == EOF)
                    break;
            }

            auto& tile{getTile(x, y)};
            switch (sign)
            {
                case '1':
                    tile = std::make_unique<Brick>();
                    break;
                case '2':
                    tile = std::make_unique<Water>();
                    break;
                case '3':
                    tile = std::make_unique<Plant>();
                    break;
                case '4':
                    tile = std::make_unique<Ice>();
                    break;
                case '5':
                    tile = std::make_unique<Steel>();
                    break;
                case '6':
                    tile = std::make_unique<Base>();
                    break;
                case 'M':
                    tile = std::make_unique<Plain>();
                    tanks.emplace_back(TankType::PLAYER_TIER_1,
                                       Config::elementSize * x,
                                       Config::elementSize * y);
                    break;
                case 'E':
                    tile = std::make_unique<Plain>();
                    tanks.emplace_back(TankType::ENEMY_TIER_1,
                                       Config::elementSize * x,
                                       Config::elementSize * y);
                    break;
                case 'A':
                    tile = std::make_unique<ShieldUp>();
                    break;
                case 'S':
                    tile = std::make_unique<SpeedUp>();
                    break;
                case 'L':
                    tile = std::make_unique<TierUp>();
                    break;
                case 'T':
                    tile = std::make_unique<LifeUp>();
                    break;
                default:
                    tile = std::make_unique<Plain>();
            }
        }

    const int off{clock()};
    std::cout << "loadMap " << (static_cast<float>(off - on)) / CLOCKS_PER_SEC
              << " seconds" << std::endl;

    return tanks;
}

void Map::drawMapItem(const Screen& screen, ResourceType resourceType,
                      unsigned int x, unsigned int y)
{
    screen.drawScaledBitmap(resourceType, x, y, Config::elementSize);
}

bool Map::canDrive(unsigned int x, unsigned int y) const
{
    return getTile(x, y)->canDrive();
}

bool Map::isValid(int x, int y)
{
    const int maxCoordinate{
        static_cast<int>((Config::mapSize - 1) * Config::elementSize)};
    return x >= 0 && x < maxCoordinate && y >= 0 && y < maxCoordinate;
}

std::pair<bool, ResourceType> Map::takePowerUp(unsigned int x, unsigned int y)
{
    auto& tile{getTile(x, y)};
    if (!tile->isPowerUp())
        return {false, ResourceType::PLAIN};
    const ResourceType type{tile->getResourceType()};
    tile = std::make_unique<Plain>();
    return {true, type};
}

bool Map::canFly(unsigned int x, unsigned int y) const
{
    return getTile(x, y)->canFly();
}

void Map::destroyItem(unsigned int x, unsigned int y, unsigned int power)
{
    auto& tile{getTile(x, y)};
    if (tile->destroy(power))
    {
        bool baseDestroyed{tile->getResourceType() == ResourceType::BASE};
        tile = std::make_unique<Plain>();
        if (baseDestroyed)
            playerDestroyed_ = true;
    }
}

void Map::drawBackground(const Screen& screen)
{
    for (unsigned int x = 0; x < Config::mapSize; x++)
        for (unsigned int y = 0; y < Config::mapSize; y++)
        {
            const auto& tile{getTile(x, y)};
            ResourceType type{tile->getResourceType()};
            if (!tile->isPartOfBackground())
                type = ResourceType::PLAIN;

            drawMapItem(screen, type, x * Config::elementSize,
                        y * Config::elementSize);
        }
}

void Map::drawForeground(const Screen& screen)
{
    for (unsigned int x = 0; x < Config::mapSize; x++)
        for (unsigned int y = 0; y < Config::mapSize; y++)
        {
            const auto& tile{getTile(x, y)};
            if (!tile->isPartOfBackground())
                drawMapItem(screen, tile->getResourceType(),
                            x * Config::elementSize, y * Config::elementSize);
        }
}

bool Map::isPlayerDestroyed() const { return playerDestroyed_; }
