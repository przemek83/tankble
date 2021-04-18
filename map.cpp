#include "map.h"
#include "config.h"
#include "map/bullet.h"
#include "map/powerup.h"
#include "player.h"
#include "vehicle.h"

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
    int off;
    FILE* plik;
    const char* source = "missions/mission1.dat";
    if ((plik = fopen(source, "r")) == NULL)
    {
        // return false;
        exit(1);
    }
    int sign;
    for (unsigned int i = 0; i < Config::mapSize; i++)
        for (unsigned int j = 0; j < Config::mapSize; j++)
        {
            sign = fgetc(plik);
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
                    board_[i][j] = new Brick();
                    break;
                case '2':
                    board_[i][j] = new Water();
                    break;
                case '3':
                    board_[i][j] = new Plant();
                    break;
                case '4':
                    board_[i][j] = new Ice();
                    break;
                case '5':
                    board_[i][j] = new Steel();
                    break;
                case '6':
                    board_[i][j] = new Base();
                    break;
                case 'M':
                    board_[i][j] = new Plain();
                    player_->loadVehicle(new Vehicle(0, Config::elementSize * j,
                                                     Config::elementSize * i));
                    vehicles.push_back(player_->getVehicle());
                    break;
                case 'E':
                    board_[i][j] = new Plain();
                    vehicles.push_back(new Vehicle(4, Config::elementSize * j,
                                                   Config::elementSize * i));
                    break;
                case 'A':
                    board_[i][j] = new ArmorUp();
                    break;
                case 'S':
                    board_[i][j] = new SpeedUp();
                    break;
                case 'L':
                    board_[i][j] = new LevelUp();
                    break;
                case 'T':
                    board_[i][j] = new TankUp();
                    break;
                default:
                    board_[i][j] = new Plain();
            }
        }
    fclose(plik);
    off = clock();
    std::cout << "loadMap " << (static_cast<float>(off - on)) / CLOCKS_PER_SEC
              << " seconds" << std::endl;
}

void Map::drawMapItem(ALLEGRO_BITMAP* element, int x, int y)
{
    al_draw_scaled_bitmap(element, 0, 0, al_get_bitmap_width(element),
                          al_get_bitmap_height(element), x, y,
                          Config::elementSize, Config::elementSize, 0);
}

Map::Map(Player* player)
{
    buffer_ = al_create_bitmap(Config::mapSize * Config::elementSize,
                               Config::mapSize * Config::elementSize);
    paint_ = al_create_bitmap(Config::mapSize * Config::elementSize,
                              Config::mapSize * Config::elementSize);
    player_ = player;
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

    Tile* m;
    for (unsigned int i = 0; i < Config::mapSize; i++)
    {
        for (unsigned int j = 0; j < Config::mapSize; j++)
        {
            m = (Tile*)board_[i][j];
            delete m;
        }
    }
    al_destroy_bitmap(buffer_);
    al_destroy_bitmap(paint_);
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
    Vehicle* v;
    for (unsigned int i = 0; i < vehicles.size(); i++)
    {
        v = vehicles.at(i);
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
        Tile* e = board_[i][j];
        board_[i][j] = new Plain();
        if (e->getId() == 6)
        {
            throw Lose();
        }
        delete e;
        al_set_target_bitmap(paint_);
        drawMapItem(board_[i][j]->display(), j * Config::elementSize,
                    i * Config::elementSize);
    }
}

void Map::addBullet(Bullet* bullet) { bullets_.push_back(bullet); }

void Map::setPower(Vehicle* v)
{
    int j = (v->getX() + 15) / Config::elementSize;
    int i = (v->getY() + 15) / Config::elementSize;

    if (board_[i][j]->getId() > 20)
    {
        if (board_[i][j]->getArmorUp())
        {
            v->setMaxArmor();
        }
        else if (board_[i][j]->getLevelUp())
        {
            if (v->getType() < 3)
            {
                v->setType(v->getType() + 1);
            }
        }
        else if (board_[i][j]->getSpeedUp())
        {
            v->setSpeedUp();
        }
        else if (board_[i][j]->getTankUp())
        {
            player_->setTanks(player_->getTanks() + 1);
        }
        Tile* e = board_[i][j];
        board_[i][j] = new Plain();
        delete e;

        al_set_target_bitmap(paint_);
        drawMapItem(board_[i][j]->display(), j * Config::elementSize,
                    i * Config::elementSize);
    }
}
