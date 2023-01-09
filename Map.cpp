#include "Map.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "Config.h"
#include "Resources.h"
#include "Vehicle.h"
#include "map/Base.h"
#include "map/Brick.h"
#include "map/Bullet.h"
#include "map/Ice.h"
#include "map/Plain.h"
#include "map/Plant.h"
#include "map/Powerup.h"
#include "map/Steel.h"
#include "map/Water.h"

Map::Map(const Resources& resources) : resources_(resources)
{
    buffer_ = al_create_bitmap(Config::mapSize * Config::elementSize,
                               Config::mapSize * Config::elementSize);
    paint_ = al_create_bitmap(Config::mapSize * Config::elementSize,
                              Config::mapSize * Config::elementSize);

    board_.reserve(Config::mapSize * Config::mapSize);
    board_.resize(Config::mapSize);
    for (auto& item : board_)
        item.resize(Config::mapSize);
    loadMap();
    al_set_target_bitmap(paint_);
    for (unsigned int i = 0; i < Config::mapSize; i++)
        for (unsigned int j = 0; j < Config::mapSize; j++)
            drawMapItem(resources_.getBitmap(board_[i][j]->getResourceType()),
                        j * Config::elementSize, i * Config::elementSize);
}

Map::~Map()
{
    if (!vehicles_.empty())
        vehicles_.clear();

    al_destroy_bitmap(buffer_);
    al_destroy_bitmap(paint_);
}

ALLEGRO_BITMAP* Map::display()
{
    displayMaps();
    displayVehicles();
    displayBullets();
    return buffer_;
}

void Map::displayMaps()
{
    al_set_target_bitmap(buffer_);
    al_draw_bitmap_region(paint_, 0, 0, Config::elementSize * Config::mapSize,
                          Config::elementSize * Config::mapSize, 0, 0, 0);
}

void Map::displayVehicles()
{
    for (const auto& vehicle : vehicles_)
    {
        al_set_target_bitmap(buffer_);
        drawMapItem(vehicle->display(), vehicle->getX(), vehicle->getY());
    }
}

void Map::displayBullets()
{
    for (const auto& bullet : bullets_)
    {
        al_set_target_bitmap(buffer_);
        al_draw_bitmap_region(bullet->display(), 0, 0,
                              al_get_bitmap_width(bullet->display()),
                              al_get_bitmap_height(bullet->display()),
                              bullet->getX(), bullet->getY(), 0);
    }
}

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
                Vehicle* v{vehicles_.at(iter)};
                if (v->destroy(b->getPower()))
                {
                    if (v->isPlayerControlled())
                        playerDestroyed_ = true;
                    delete vehicles_[iter];
                    vehicles_.erase(vehicles_.begin() + iter);
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
                    vehicles_.push_back(new Vehicle(TankType::PLAYER_TIER_1,
                                                    Config::elementSize * j,
                                                    Config::elementSize * i));
                    break;
                case 'E':
                    board_[i][j] = std::make_unique<Plain>();
                    vehicles_.push_back(new Vehicle(TankType::ENEMY_TIER_1,
                                                    Config::elementSize * j,
                                                    Config::elementSize * i));
                    break;
                case 'A':
                    board_[i][j] = std::make_unique<ArmorUp>();
                    break;
                case 'S':
                    board_[i][j] = std::make_unique<SpeedUp>();
                    break;
                case 'L':
                    board_[i][j] = std::make_unique<LevelUp>();
                    break;
                case 'T':
                    board_[i][j] = std::make_unique<TankUp>();
                    break;
                default:
                    board_[i][j] = std::make_unique<Plain>();
            }
        }

    int off{clock()};
    std::cout << "loadMap " << (static_cast<float>(off - on)) / CLOCKS_PER_SEC
              << " seconds" << std::endl;
}

void Map::drawMapItem(ALLEGRO_BITMAP* element, int x, int y)
{
    al_draw_scaled_bitmap(element, 0, 0, al_get_bitmap_width(element),
                          al_get_bitmap_height(element), x, y,
                          Config::elementSize, Config::elementSize, 0);
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
    for (unsigned int i = 0; i < vehicles_.size(); i++)
    {
        Vehicle* v{vehicles_.at(i)};
        if (bullet->getCenterX() >= v->getX() &&
            bullet->getCenterX() < v->getX() + Config::elementSize &&
            bullet->getCenterY() >= v->getY() &&
            bullet->getCenterY() < v->getY() + Config::elementSize &&
            bullet->getTankType() != v->getTankType())
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
        al_set_target_bitmap(paint_);
        drawMapItem(resources_.getBitmap(board_[i][j]->getResourceType()),
                    j * Config::elementSize, i * Config::elementSize);
    }
}

void Map::addBullet(std::unique_ptr<Bullet> bullet)
{
    bullets_.emplace_back(std::move(bullet));
}

void Map::setPower(Vehicle* vehicle)
{
    const std::size_t j{(vehicle->getX() + 15) / Config::elementSize};
    const std::size_t i{(vehicle->getY() + 15) / Config::elementSize};

    std::unique_ptr<Tile>& tile{board_[i][j]};
    if (!tile->isPowerUp())
        return;

    switch (tile->getResourceType())
    {
        case ResourceType::ARMOR_UP:
            vehicle->setMaxArmor();
            break;

        case ResourceType::LEVEL_UP:
            if (static_cast<int>(vehicle->getTankType()) < 3)
                vehicle->setType(static_cast<TankType>(
                    static_cast<int>(vehicle->getTankType()) + 1));
            break;

        case ResourceType::SPEED_UP:
            vehicle->setSpeedUp();
            break;

        case ResourceType::TANK_UP:
            vehicle->addLife();
            break;

        default:
            break;
    }

    tile = std::make_unique<Plain>();

    al_set_target_bitmap(paint_);
    drawMapItem(resources_.getBitmap(board_[i][j]->getResourceType()),
                j * Config::elementSize, i * Config::elementSize);
}

const std::vector<Vehicle*>& Map::getVehicles() const { return vehicles_; }

bool Map::isPlayerDestroyed() const { return playerDestroyed_; }
