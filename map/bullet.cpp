#include "bullet.h"
#include <allegro5/allegro.h>
#include <cstdio>
#include "../vehicle.h"

Bullet::Bullet(Vehicle* v)
{
    this->source = "image/plansza/pocisk.tga";
    if (!loadBitmap())
    {
        exit(0);
    }
    this->id = v->getId();
    this->direction = v->getDirection();
    this->speed = v->getSpeed();
    this->power = v->getPower();
    this->x = v->getX() + E_SIZE / 2 - 3;
    this->y = v->getY() + E_SIZE / 2 - 3;
    this->vehicle = v;
}

Bullet::~Bullet()
{
    al_destroy_bitmap(this->bmp);
    try
    {
        this->vehicle->resetFire();
    }
    catch (...)
    {
    }
    cout << "Bullet: " << this->getId() << " is deleted\n";
}

bool Bullet::loadBitmap()
{
    FILE* fp;
    if ((fp = fopen(source, "r")) == NULL)
    {
        return false;
    }
    fclose(fp);
    this->bmp = al_load_bitmap(this->source);  //, palette);
    return true;
}

ALLEGRO_BITMAP* Bullet::display() { return this->bmp; }

int Bullet::getId() { return this->id; }

int Bullet::getPower() { return this->power; }

int Bullet::getSpeed() { return this->speed; }

int Bullet::getDirection() { return this->direction; }

int Bullet::getX() { return this->x; }

int Bullet::getY() { return this->y; }

int Bullet::getCenterX() { return this->x + 3; }

int Bullet::getCenterY() { return this->y + 3; }

void Bullet::setX(int x) { this->x = x; }

void Bullet::setY(int y) { this->y = y; }

int Bullet::getDirectionX()
{
    if (this->direction == 1)
        return 1;
    if (this->direction == 3)
        return -1;
    return 0;
}

int Bullet::getDirectionY()
{
    if (this->direction == 0)
        return -1;
    if (this->direction == 2)
        return 1;
    return 0;
}
