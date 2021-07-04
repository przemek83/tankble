#include "Map.h"

#include "Config.h"
#include "Player.h"
#include "Vehicle.h"
#include "map/Bullet.h"
#include "map/Powerup.h"

Map::Map(Player* player)
{
    buffer_ = al_create_bitmap(Config::mapSize * Config::elementSize,
                               Config::mapSize * Config::elementSize);
    paint_ = al_create_bitmap(Config::mapSize * Config::elementSize,
                              Config::mapSize * Config::elementSize);
    player_ = player;
    board_.reserve(Config::mapSize * Config::mapSize);
    board_.resize(Config::mapSize);
    for (auto& item : board_)
        item.resize(Config::mapSize);
    loadMap();
    al_set_target_bitmap(paint_);
    for (unsigned int i = 0; i < Config::mapSize; i++)
        for (unsigned int j = 0; j < Config::mapSize; j++)
            drawMapItem(board_[i][j]->display(), j * Config::elementSize,
                        i * Config::elementSize);
}

Map::~Map()
{
    if (!bullets_.empty())
        bullets_.clear();
    if (!vehicles.empty())
        vehicles.clear();

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
    for (const auto& vehicle : vehicles)
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
    Bullet* b;
    int px, py;
    unsigned int pi, pj;
    Vehicle* v;
    Vehicle* n;
    for (unsigned int i = 0; i < bullets_.size(); i++)
    {
        b = bullets_.at(i);
        px = b->getX() + b->getDirectionX() * b->getSpeed();
        py = b->getY() + b->getDirectionY() * b->getSpeed();
        if (isBulletValid(px, py))
        {
            b->setX(px);
            b->setY(py);
            pi = b->getCenterY() / Config::elementSize;
            pj = b->getCenterX() / Config::elementSize;
            if (!canFly(pj, pi))
            {
                destroyItem(pj, pi, b->getPower());
                delete bullets_[i];
                bullets_.erase(bullets_.begin() + i);
            }
            int iter = isTank(b);
            if (iter >= 0)
            {
                v = vehicles.at(iter);
                if (v->destroy(b->getPower()))
                {
                    if (v == player_->getVehicle())
                    {
                        n = player_->killVehicle();
                        delete vehicles[iter];
                        vehicles.push_back(n);
                    }
                    else
                    {
                        delete vehicles[iter];
                    }
                    vehicles.erase(vehicles.begin() + iter);
                }
                delete bullets_[i];
                bullets_.erase(bullets_.begin() + i);
            }
        }
        else
        {
            delete bullets_[i];
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
    FILE* plik{nullptr};
    const char* source = "missions/mission1.dat";
    if ((plik = fopen(source, "r")) == nullptr)
    {
        // return false;
        exit(1);
    }
    for (unsigned int i = 0; i < Config::mapSize; i++)
        for (unsigned int j = 0; j < Config::mapSize; j++)
        {
            int sign{fgetc(plik)};
            while ((sign < '0' || sign >= '8') && sign != 'T' && sign != 'E' &&
                   sign != 'M' && sign != 'S' && sign != 'L' && sign != 'A')
            {
                sign = fgetc(plik);
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
                    player_->loadVehicle(new Vehicle(0, Config::elementSize * j,
                                                     Config::elementSize * i));
                    vehicles.push_back(player_->getVehicle());
                    break;
                case 'E':
                    board_[i][j] = std::make_unique<Plain>();
                    vehicles.push_back(new Vehicle(4, Config::elementSize * j,
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
    fclose(plik);
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

int Map::isTank(Bullet* b)
{
    for (unsigned int i = 0; i < vehicles.size(); i++)
    {
        Vehicle* v{vehicles.at(i)};
        if (b->getCenterX() >= v->getX() &&
            b->getCenterX() < v->getX() + Config::elementSize &&
            b->getCenterY() >= v->getY() &&
            b->getCenterY() < v->getY() + Config::elementSize &&
            b->getId() / 100 != v->getId() / 100)
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
        bool baseDestroyed{board_[i][j]->getId() == Tile::Type::BASE};
        board_[i][j] = std::make_unique<Plain>();
        if (baseDestroyed)
            throw Lose();
        al_set_target_bitmap(paint_);
        drawMapItem(board_[i][j]->display(), j * Config::elementSize,
                    i * Config::elementSize);
    }
}

void Map::addBullet(Bullet* bullet) { bullets_.push_back(bullet); }

void Map::setPower(Vehicle* v)
{
    const std::size_t j{(v->getX() + 15) / Config::elementSize};
    const std::size_t i{(v->getY() + 15) / Config::elementSize};

    std::unique_ptr<Tile>& tile{board_[i][j]};
    if (!tile->isPowerUp())
        return;

    switch (tile->getId())
    {
        case Tile::Type::ARMOR_UP:
            v->setMaxArmor();
            break;

        case Tile::Type::LEVEL_UP:
            if (v->getType() < 3)
                v->setType(v->getType() + 1);
            break;

        case Tile::Type::SPEED_UP:
            v->setSpeedUp();
            break;

        case Tile::Type::TANK_UP:
            player_->setTanks(player_->getTanks() + 1);
            break;

        default:
            break;
    }

    tile = std::make_unique<Plain>();

    al_set_target_bitmap(paint_);
    drawMapItem(board_[i][j]->display(), j * Config::elementSize,
                i * Config::elementSize);
}
