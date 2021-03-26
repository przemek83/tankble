#include "bullet.h"
#include <allegro5/allegro.h>
#include <cstdio>
#include "../vehicle.h"

Bullet::Bullet(Vehicle* v)
{
    source_ = "image/board/bullet.tga";
    if (!loadBitmap())
        exit(0);
    id_ = v->getId();
    direction_ = v->getDirection();
    speed_ = v->getSpeed();
    power_ = v->getPower();
    x_ = v->getX() + E_SIZE / 2 - 3;
    y_ = v->getY() + E_SIZE / 2 - 3;
    vehicle_ = v;
}

Bullet::~Bullet()
{
    al_destroy_bitmap(bmp_);
    try
    {
        vehicle_->resetFire();
    }
    catch (...)
    {
    }
    std::cout << "Bullet: " << getId() << " is deleted\n";
}

bool Bullet::loadBitmap()
{
    FILE* fp;
    if ((fp = fopen(source_, "r")) == NULL)
    {
        return false;
    }
    fclose(fp);
    bmp_ = al_load_bitmap(source_);  //, palette);
    return true;
}

ALLEGRO_BITMAP* Bullet::display() { return bmp_; }

int Bullet::getId() { return id_; }

int Bullet::getPower() { return power_; }

int Bullet::getSpeed() { return speed_; }

int Bullet::getDirection() { return direction_; }

int Bullet::getX() { return x_; }

int Bullet::getY() { return y_; }

int Bullet::getCenterX() { return x_ + 3; }

int Bullet::getCenterY() { return y_ + 3; }

void Bullet::setX(int newX) { x_ = newX; }

void Bullet::setY(int newY) { y_ = newY; }

int Bullet::getDirectionX()
{
    if (direction_ == 1)
        return 1;
    if (direction_ == 3)
        return -1;
    return 0;
}

int Bullet::getDirectionY()
{
    if (direction_ == 0)
        return -1;
    if (direction_ == 2)
        return 1;
    return 0;
}
