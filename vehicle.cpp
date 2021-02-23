#include "vehicle.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "config.h"
#include "map.h"

const int Vehicle::wayX[4] = {0, 1, 0, -1};
const int Vehicle::wayY[4] = {-1, 0, 1, 0};
const int Vehicle::powers[8] = {2, 4, 8, 16, 1, 2, 4, 8};
const int Vehicle::armors[8] = {8, 16, 32, 64, 4, 8, 16, 32};
const int Vehicle::speeds[8] = {4, 4, 6, 8, 4, 4, 6, 8};
const int Vehicle::ids[8] = {101, 102, 103, 104, 201, 202, 203, 204};
const int Vehicle::directions[8] = {0, 0, 0, 0, 2, 2, 2, 2};
const char* Vehicle::sources[8][4] = {
    {"image/plansza/swoj_mark_1_0.tga", "image/plansza/swoj_mark_1_1.tga",
     "image/plansza/swoj_mark_1_2.tga", "image/plansza/swoj_mark_1_3.tga"},
    {"image/plansza/swoj_mark_2_0.tga", "image/plansza/swoj_mark_2_1.tga",
     "image/plansza/swoj_mark_2_2.tga", "image/plansza/swoj_mark_2_3.tga"},
    {"image/plansza/swoj_mark_3_0.tga", "image/plansza/swoj_mark_3_1.tga",
     "image/plansza/swoj_mark_3_2.tga", "image/plansza/swoj_mark_3_3.tga"},
    {"image/plansza/swoj_mark_4_0.tga", "image/plansza/swoj_mark_4_1.tga",
     "image/plansza/swoj_mark_4_2.tga", "image/plansza/swoj_mark_4_3.tga"},
    {"image/plansza/czolg_mark_1_0.tga", "image/plansza/czolg_mark_1_1.tga",
     "image/plansza/czolg_mark_1_2.tga", "image/plansza/czolg_mark_1_3.tga"},
    {"image/plansza/czolg_mark_2_0.tga", "image/plansza/czolg_mark_2_1.tga",
     "image/plansza/czolg_mark_2_2.tga", "image/plansza/czolg_mark_2_3.tga"},
    {"image/plansza/czolg_mark_3_0.tga", "image/plansza/czolg_mark_3_1.tga",
     "image/plansza/czolg_mark_3_2.tga", "image/plansza/czolg_mark_3_3.tga"},
    {"image/plansza/czolg_mark_4_0.tga", "image/plansza/czolg_mark_4_1.tga",
     "image/plansza/czolg_mark_4_2.tga", "image/plansza/czolg_mark_4_3.tga"}};

Vehicle::Vehicle(int typ, uint x, uint y)
{
    this->fly = 0;
    this->drive = 1;

    this->setX(x);
    this->setY(y);

    this->direction = this->directions[typ];
    this->setType(typ);

    if (!loadBitmaps())
    {
        exit(0);
    }

    this->lastFire = 0;
}

Vehicle::~Vehicle()
{
    al_destroy_bitmap(this->bmp[0]);
    al_destroy_bitmap(this->bmp[1]);
    al_destroy_bitmap(this->bmp[2]);
    al_destroy_bitmap(this->bmp[3]);
    cout << "Vehicle:" << this->getId() << " is deleted\n";
}

bool Vehicle::loadBitmaps()
{
    FILE* fp;

    for (int i = 0; i < 4; i++)
    {
        if ((fp = fopen(*(source + i), "r")) == NULL)
        {
            return false;
        }
        fclose(fp);
        this->bmp[i] = al_load_bitmap(*(source + i));  //, palette);
    }
    return true;
}

int Vehicle::getId() { return this->id; }

void Vehicle::setType(int typ)
{
    if (typ < 0 || typ > 7)
    {
        typ = 0;
    }
    this->id = this->ids[typ];
    this->armor = this->armors[typ];
    this->maxArmor = this->armors[typ];
    this->power = this->powers[typ];
    this->speed = this->speeds[typ];

    this->source = this->sources[typ];
    if (!this->loadBitmaps())
    {
        exit(1);
    }
}

void Vehicle::move(int xy) { this->direction = xy; }

ALLEGRO_BITMAP* Vehicle::display() { return this->bmp[this->getDirection()]; }

void Vehicle::fire(void* map)
{
    Map* mapa = (Map*)map;
    time_t ti = time(NULL);
    if (difftime(ti, this->lastFire) > 1.0)
    {
        this->lastFire = ti;
        Bullet* bullet = new Bullet(this);
        mapa->addBullet(bullet);
    }
}

bool Vehicle::destroy(int power)
{
    this->armor -= power;
    if (this->armor <= 0)
        return true;
    return false;
}

int Vehicle::getMaxArmor() { return this->maxArmor; }

int Vehicle::getType()
{
    return (this->getId() % 100) - 1;
    /*0-3*/
}

int Vehicle::getX() { return this->x; }
int Vehicle::getY() { return this->y; }
void Vehicle::setX(int x) { this->x = x; }
void Vehicle::setY(int y) { this->y = y; }
int Vehicle::getArmor() { return this->armor; }
void Vehicle::setArmor(int armor) { this->armor = armor; }

void Vehicle::setMaxArmor() { this->armor = this->getMaxArmor(); }

bool Vehicle::canFly() { return this->fly; }

bool Vehicle::canDrive() { return this->drive; }

void Vehicle::setSpeedUp() { this->speed++; }

int Vehicle::getPower() { return this->power; }

int Vehicle::getSpeed() { return this->speed; }

int Vehicle::getDirection() { return this->direction; }

int Vehicle::getDirectionX() { return this->wayX[this->getDirection()]; }

int Vehicle::getDirectionY() { return this->wayY[this->getDirection()]; }

void Vehicle::resetFire() { this->lastFire--; }

void Vehicle::go()
{
    this->setX(this->getX() + this->getDirectionX() + this->getDirectionX());
    this->setY(this->getY() + this->getDirectionY() + this->getDirectionY());
}

void Vehicle::moveRandom(void* map)
{
    int i;
    Map* mapa = (Map*)map;
    if (this->getX() % E_SIZE == 0 && this->getY() % E_SIZE == 0)
    {
        i = rand() % 8;
        if (i < 4)
        {
            this->direction = i;
        }
        if (!(mapa->isValid(
                this->getX() + this->getDirectionX() + this->getDirectionX(),
                this->getY() + this->getDirectionY() + this->getDirectionY())))
        {
            return;
        }
        if (!mapa->canDrive(this->getX() / E_SIZE + this->getDirectionX(),
                            this->getY() / E_SIZE + this->getDirectionY()))
        {
            return;
        }
    }
    this->go();
}
