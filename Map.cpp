#include "Map.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include <allegro5/allegro.h>

#include "Config.h"
#include "Resources.h"
#include "Screen.h"
#include "Tank.h"
#include "map/Base.h"
#include "map/Brick.h"
#include "map/Bullet.h"
#include "map/Ice.h"
#include "map/LifeUp.h"
#include "map/Plain.h"
#include "map/Plant.h"
#include "map/ShieldUp.h"
#include "map/SpeedUp.h"
#include "map/Steel.h"
#include "map/TierUp.h"
#include "map/Water.h"

Map::Map(const Resources& resources) : resources_(resources)
{
    board_.reserve(Config::mapSize * Config::mapSize);
    board_.resize(Config::mapSize);
    for (auto& item : board_)
        item.resize(Config::mapSize);
    loadMap();
}

Map::~Map() {}

void Map::moveBullet()
{
    for (unsigned int i = 0; i < bullets_.size(); i++)
    {
        std::unique_ptr<Bullet>& b{bullets_.at(i)};
        int px{b->getX() + b->getDirectionX() * b->getSpeed()};
        int py{b->getY() + b->getDirectionY() * b->getSpeed()};
        if (isBulletValid(px, py))
        {
            b->setX(px);
            b->setY(py);
            unsigned int pi{b->getCenterY() / Config::elementSize};
            unsigned int pj{b->getCenterX() / Config::elementSize};
            int iter{isTank(b)};
            if (!canFly(pj, pi))
            {
                destroyItem(pj, pi, b->getPower());
                bullets_.erase(bullets_.begin() + i);
            }
            if (iter >= 0)
            {
                Tank& v{tanks_.at(iter)};
                if (v.destroy(b->getPower()))
                {
                    if (v.isPlayerControlled())
                        playerDestroyed_ = true;
                    tanks_.erase(tanks_.begin() + iter);
                }
                bullets_.erase(bullets_.begin() + i);
            }
        }
        else
        {
            bullets_.erase(bullets_.begin() + i);
        }
    }
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

void Map::loadMap()
{
    int on = clock();

    if (!std::filesystem::exists("missions/mission1.dat"))
        exit(1);

    char sign;
    std::fstream fin("missions/mission1.dat", std::fstream::in);

    for (unsigned int i = 0; i < Config::mapSize; i++)
        for (unsigned int j = 0; j < Config::mapSize; j++)
        {
            fin >> std::noskipws >> sign;

            while ((sign < '0' || sign >= '8') && sign != 'T' && sign != 'E' &&
                   sign != 'M' && sign != 'S' && sign != 'L' && sign != 'A')
            {
                fin >> std::noskipws >> sign;
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
                    tanks_.emplace_back(TankType::PLAYER_TIER_1,
                                        Config::elementSize * j,
                                        Config::elementSize * i);
                    break;
                case 'E':
                    board_[i][j] = std::make_unique<Plain>();
                    tanks_.emplace_back(TankType::ENEMY_TIER_1,
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

    int off{clock()};
    std::cout << "loadMap " << (static_cast<float>(off - on)) / CLOCKS_PER_SEC
              << " seconds" << std::endl;
}

void Map::drawMapItem(const Screen& screen, ResourceType resourceType, int x,
                      int y)
{
    screen.drawScaledBitmap(resourceType, x, y, Config::elementSize);
}

bool Map::canDrive(unsigned int j, unsigned int i)
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

bool Map::isBulletValid(int x, int y)
{
    const int bulletSize{7};
    if (x >= Config::elementSize * Config::mapSize - bulletSize ||
        y >= Config::elementSize * Config::mapSize - bulletSize || y < 0 ||
        x < 0)
    {
        return false;
    }
    return true;
}

bool Map::canFly(unsigned int j, unsigned int i)
{
    return board_[i][j]->canFly();
}

int Map::isTank(const std::unique_ptr<Bullet>& bullet)
{
    for (unsigned int i = 0; i < tanks_.size(); i++)
    {
        const Tank& v{tanks_.at(i)};
        if (bullet->getCenterX() >= v.getX() &&
            bullet->getCenterX() < v.getX() + Config::elementSize &&
            bullet->getCenterY() >= v.getY() &&
            bullet->getCenterY() < v.getY() + Config::elementSize &&
            bullet->getTankType() != v.getTankType())
        {  // check friendly fire
            return i;
        }
    }
    return -1;
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

void Map::addBullet(std::unique_ptr<Bullet> bullet)
{
    bullets_.emplace_back(std::move(bullet));
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

void Map::drawPowers(Screen& screen) {}

void Map::drawVehicles(const Screen& screen)
{
    for (const auto& vehicle : tanks_)
    {
        ResourceType resourceType = static_cast<ResourceType>(
            static_cast<unsigned char>(ResourceType::PLAYER_TANK_TIER_1) +
            static_cast<unsigned char>(vehicle.getTankType()));

        screen.drawScaledBitmapWithRotation(resourceType, vehicle.getX(),
                                            vehicle.getY(), Config::elementSize,
                                            90 * vehicle.getDirection());
    }
}

void Map::drawBullets(const Screen& screen)
{
    const ResourceType resourceType = Bullet::getResourceType();
    for (const auto& bullet : bullets_)
    {
        screen.drawScaledBitmap(resourceType, bullet->getX(), bullet->getY(),
                                Config::BULLET_SIZE);
    }
}

std::vector<Tank>& Map::getTanks() { return tanks_; }

bool Map::isPlayerDestroyed() const { return playerDestroyed_; }
