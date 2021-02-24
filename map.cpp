#include "map.h"
#include "config.h"
#include "map/bullet.h"
#include "map/powerup.h"
#include "player.h"
#include "vehicle.h"

ALLEGRO_BITMAP* Map::display()
{
    this->displayMaps();
    this->displayVehicles();
    this->displayBullets();
    return this->buffer;
}

void Map::displayMaps()
{
    al_set_target_bitmap(buffer);
    al_draw_bitmap_region(paint, 0, 0, E_SIZE * MAP_SIZE, E_SIZE * MAP_SIZE, 0,
                          0, 0);
}

void Map::displayVehicles()
{
    for (uint i = 0; i < vehicles.size(); i++)
    {
        al_set_target_bitmap(buffer);
        al_draw_bitmap(vehicles.at(i)->display(), vehicles.at(i)->getX(),
                       vehicles.at(i)->getY(), 0);
    }
}

void Map::displayBullets()
{
    for (uint i = 0; i < bullets.size(); i++)
    {
        al_set_target_bitmap(buffer);
        al_draw_bitmap_region(bullets.at(i)->display(), 0, 0,
                              al_get_bitmap_width(bullets.at(i)->display()),
                              al_get_bitmap_height(bullets.at(i)->display()),
                              bullets.at(i)->getX(), bullets.at(i)->getY(), 0);
    }
}

void Map::moveBullet()
{
    Bullet* b;
    int px, py;
    uint pi, pj;
    int iter = -1;
    Vehicle* v;
    Vehicle* n;
    for (uint i = 0; i < bullets.size(); i++)
    {
        b = this->bullets.at(i);
        px = b->getX() + b->getDirectionX() * b->getSpeed();
        py = b->getY() + b->getDirectionY() * b->getSpeed();
        if (isBulletValid(px, py))
        {
            b->setX(px);
            b->setY(py);
            pi = b->getCenterY() / E_SIZE;
            pj = b->getCenterX() / E_SIZE;
            if (!this->canFly(pj, pi))
            {
                this->destroyItem(pj, pi, b->getPower());
                delete this->bullets[i];
                this->bullets.erase(bullets.begin() + i);
            }
            iter = this->isTank(b);
            if (iter >= 0)
            {
                v = this->vehicles.at(iter);
                if (v->destroy(b->getPower()))
                {
                    if (v == this->player->getVehicle())
                    {
                        n = this->player->killVehicle();
                        delete this->vehicles[iter];
                        this->vehicles.push_back(n);
                    }
                    else
                    {
                        delete this->vehicles[iter];
                    }
                    this->vehicles.erase(vehicles.begin() + iter);
                }
                delete this->bullets[i];
                this->bullets.erase(bullets.begin() + i);
            }
        }
        else
        {
            delete this->bullets[i];
            this->bullets.erase(bullets.begin() + i);
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
    for (uint i = 0; i < MAP_SIZE; i++)
        for (uint j = 0; j < MAP_SIZE; j++)
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
                    board[i][j] = new Bricks();
                    break;
                case '2':
                    board[i][j] = new Water();
                    break;
                case '3':
                    board[i][j] = new Plants();
                    break;
                case '4':
                    board[i][j] = new Ice();
                    break;
                case '5':
                    board[i][j] = new Steel();
                    break;
                case '6':
                    board[i][j] = new Plain();
                    break;
                case 'M':
                    board[i][j] = new Dirt();
                    this->player->loadVehicle(
                        new Vehicle(0, E_SIZE * j, E_SIZE * i));
                    vehicles.push_back(this->player->getVehicle());
                    break;
                case 'E':
                    board[i][j] = new Dirt();
                    vehicles.push_back(new Vehicle(4, E_SIZE * j, E_SIZE * i));
                    break;
                case 'A':
                    board[i][j] = new ArmorUp();
                    break;
                case 'S':
                    board[i][j] = new SpeedUp();
                    break;
                case 'L':
                    board[i][j] = new LevelUp();
                    break;
                case 'T':
                    board[i][j] = new TankUp();
                    break;
                default:
                    board[i][j] = new Dirt();
            }
        }
    fclose(plik);
    off = clock();
    cout << "loadMap " << (static_cast<float>(off - on)) / CLOCKS_PER_SEC
         << " seconds" << endl;
}

void Map::drawMapItem(ALLEGRO_BITMAP* element, int x, int y)
{
    al_draw_scaled_bitmap(element, 0, 0, al_get_bitmap_width(element),
                          al_get_bitmap_height(element), x * E_SIZE, y * E_SIZE,
                          E_SIZE, E_SIZE, 0);
}

Map::Map(Player* player)
{
    this->buffer = al_create_bitmap(MAP_SIZE * E_SIZE, MAP_SIZE * E_SIZE);
    this->paint = al_create_bitmap(MAP_SIZE * E_SIZE, MAP_SIZE * E_SIZE);
    this->player = player;
    loadMap();
    al_set_target_bitmap(paint);
    for (uint i = 0; i < MAP_SIZE; i++)
        for (uint j = 0; j < MAP_SIZE; j++)
            drawMapItem(board[i][j]->display(), j, i);
}

Map::~Map()
{
    if (!this->bullets.empty())
        this->bullets.clear();
    if (!this->vehicles.empty())
        this->vehicles.clear();

    MapElement* m;
    for (uint i = 0; i < MAP_SIZE; i++)
    {
        for (uint j = 0; j < MAP_SIZE; j++)
        {
            m = (MapElement*)this->board[i][j];
            delete m;
        }
    }
    al_destroy_bitmap(this->buffer);
    al_destroy_bitmap(this->paint);
}

bool Map::canDrive(uint j, uint i) { this->board[i][j]->canDrive(); }

bool Map::isValid(int x, int y)
{
    if (x >= E_SIZE * MAP_SIZE - E_SIZE || y >= E_SIZE * MAP_SIZE - E_SIZE ||
        y < 0 || x < 0)
    {
        return false;
    }
    return true;
}

bool Map::isBulletValid(int x, int y)
{
    if (x >= E_SIZE * MAP_SIZE - B_SIZE || y >= E_SIZE * MAP_SIZE - B_SIZE ||
        y < 0 || x < 0)
    {
        return false;
    }
    return true;
}

bool Map::canFly(uint j, uint i) { return this->board[i][j]->canFly(); }

int Map::isTank(Bullet* b)
{
    Vehicle* v;
    for (uint i = 0; i < vehicles.size(); i++)
    {
        v = vehicles.at(i);
        if (b->getCenterX() >= v->getX() &&
            b->getCenterX() < v->getX() + E_SIZE &&
            b->getCenterY() >= v->getY() &&
            b->getCenterY() < v->getY() + E_SIZE &&
            b->getId() / 100 != v->getId() / 100)
        {  // check friendly fire
            return i;
        }
    }
    return -1;
}

void Map::destroyItem(uint j, uint i, uint power)
{
    if (this->board[i][j]->destroy(power))
    {
        MapElement* e = this->board[i][j];
        this->board[i][j] = new Dirt();
        if (e->getId() == 6)
        {
            throw Lose();
        }
        delete e;
        al_set_target_bitmap(paint);
        drawMapItem(board[i][j]->display(), j, i);
    }
}

void Map::addBullet(Bullet* bullet) { this->bullets.push_back(bullet); }

void Map::setPower(Vehicle* v)
{
    int j = (v->getX() + 15) / E_SIZE;
    int i = (v->getY() + 15) / E_SIZE;

    if (this->board[i][j]->getId() > 20)
    {
        if (this->board[i][j]->getArmorUp())
        {
            v->setMaxArmor();
        }
        else if (this->board[i][j]->getLevelUp())
        {
            if (v->getType() < 3)
            {
                v->setType(v->getType() + 1);
            }
        }
        else if (this->board[i][j]->getSpeedUp())
        {
            v->setSpeedUp();
        }
        else if (this->board[i][j]->getTankUp())
        {
            this->player->setTanks(player->getTanks() + 1);
        }
        MapElement* e = this->board[i][j];
        this->board[i][j] = new Dirt();
        delete e;

        al_set_target_bitmap(paint);
        drawMapItem(board[i][j]->display(), j, i);
    }
}
