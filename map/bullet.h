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
    void setX(int newX);
    void setY(int newY);
    int getDirectionX();
    int getDirectionY();

private:
    bool loadBitmap();

    ALLEGRO_BITMAP* bmp_;
    const char* source_;
    Vehicle* vehicle_;
    int id_;
    int direction_;
    int speed_;
    int power_;
    int x_;
    int y_;
};
