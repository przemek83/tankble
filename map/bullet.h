#pragma once

#include <allegro5/allegro.h>
#include "../vehicle.h"

class Bullet
{
public:
    explicit Bullet(Vehicle*);
    ~Bullet();
    ALLEGRO_BITMAP* display();
    int getId();
    int getPower();
    int getSpeed();
    int getDirection();
    int getX();
    int getY();

    int getCenterX();
    int getCenterY();
    void setX(int);
    void setY(int);
    int getDirectionX();
    int getDirectionY();

private:
    ALLEGRO_BITMAP* bmp;
    const char* source;
    int id;
    Vehicle* vehicle;
    int direction;
    int speed;
    int power;
    int x;
    int y;
    bool loadBitmap();
};
