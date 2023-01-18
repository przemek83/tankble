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
    for (unsigned int i = 0; i < Config::mapSize; i++)
        for (unsigned int j = 0; j < Config::mapSize; j++)
        {
            stream >> std::noskipws >> sign;

            while ((sign < '0' || sign >= '8') && sign != 'T' && sign != 'E' &&
                   sign != 'M' && sign != 'S' && sign != 'L' && sign != 'A')
            {
                stream >> std::noskipws >> sign;
                if (sign == EOF)
                    break;
            }

            // tab[i][j]=1;
            switch (sign)
            {
                case '1':
                    board_[i][j] = std::make_unique<Brick>();
                    break;
                case '2':
                    board_[i][j] = std::make_unique<Water>();
                    break;
                case '3':
                    board_[i][j] = std::make_unique<Plant>();
                    break;
                case '4':
                    board_[i][j] = std::make_unique<Ice>();
                    break;
                case '5':
                    board_[i][j] = std::make_unique<Steel>();
                    break;
                case '6':
                    board_[i][j] = std::make_unique<Base>();
                    break;
                case 'M':
                    board_[i][j] = std::make_unique<Plain>();
                    tanks.emplace_back(TankType::PLAYER_TIER_1,
                                       Config::elementSize * j,
                                       Config::elementSize * i);
                    break;
                case 'E':
                    board_[i][j] = std::make_unique<Plain>();
                    tanks.emplace_back(TankType::ENEMY_TIER_1,
                                       Config::elementSize * j,
                                       Config::elementSize * i);
                    break;
                case 'A':
                    board_[i][j] = std::make_unique<ShieldUp>();
                    break;
                case 'S':
                    board_[i][j] = std::make_unique<SpeedUp>();
                    break;
                case 'L':
                    board_[i][j] = std::make_unique<TierUp>();
                    break;
                case 'T':
                    board_[i][j] = std::make_unique<LifeUp>();
                    break;
                default:
                    board_[i][j] = std::make_unique<Plain>();
            }
        }

    const int off{clock()};
    std::cout << "loadMap " << (static_cast<float>(off - on)) / CLOCKS_PER_SEC
              << " seconds" << std::endl;

    return tanks;
}

void Map::drawMapItem(const Screen& screen, ResourceType resourceType, int x,
                      int y)
{
    screen.drawScaledBitmap(resourceType, x, y, Config::elementSize);
}

bool Map::canDrive(unsigned int j, unsigned int i) const
{
    return board_[i][j]->canDrive();
}

bool Map::isValid(int x, int y)
{
    if (x >= Config::elementSize * Config::mapSize - Config::elementSize ||
        y >= Config::elementSize * Config::mapSize - Config::elementSize ||
        y < 0 || x < 0)
    {
        return false;
    }
    return true;
}

bool Map::canFly(unsigned int j, unsigned int i) const
{
    return board_[i][j]->canFly();
}

void Map::destroyItem(unsigned int j, unsigned int i, unsigned int power)
{
    if (board_[i][j]->destroy(power))
    {
        bool baseDestroyed{board_[i][j]->getResourceType() ==
                           ResourceType::BASE};
        board_[i][j] = std::make_unique<Plain>();
        if (baseDestroyed)
            playerDestroyed_ = true;
    }
}

void Map::setPower(Tank& tank)
{
    const std::size_t j{(tank.getX() + 15) / Config::elementSize};
    const std::size_t i{(tank.getY() + 15) / Config::elementSize};

    std::unique_ptr<Tile>& tile{board_[i][j]};
    if (!tile->isPowerUp())
        return;

    switch (tile->getResourceType())
    {
        case ResourceType::SHIELD_UP:
            tank.setMaxArmor();
            break;

        case ResourceType::TIER_UP:
            if (static_cast<int>(tank.getTankType()) < 3)
                tank.setType(static_cast<TankType>(
                    static_cast<int>(tank.getTankType()) + 1));
            break;

        case ResourceType::SPEED_UP:
            tank.setSpeedUp();
            break;

        case ResourceType::LIFE_UP:
            tank.addLife();
            break;

        default:
            break;
    }

    tile = std::make_unique<Plain>();
}

void Map::drawBackground(const Screen& screen)
{
    for (unsigned int i = 0; i < Config::mapSize; i++)
        for (unsigned int j = 0; j < Config::mapSize; j++)
            drawMapItem(screen, board_[i][j]->getResourceType(),
                        j * Config::elementSize, i * Config::elementSize);
}

void Map::drawForeground(Screen& screen)
{
    // TODO
}

bool Map::isPlayerDestroyed() const { return playerDestroyed_; }
