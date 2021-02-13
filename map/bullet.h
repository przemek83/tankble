#ifndef BULLET_H
#define BULLET_H

#include <allegro5/allegro.h>
#include "../vehicle.h"

class Bullet
{
protected:
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

public:
    Bullet(Vehicle*);
    ~Bullet();
    ALLEGRO_BITMAP* display();  // return bitmap 30x30
    int getId();
    int getPower();
    int getSpeed();
    int getDirection();
    int getX();
    int getCenterX();
    int getCenterY();
    int getY();
    void setX(int);
    void setY(int);
    int getDirectionX();
    int getDirectionY();
};

#endif

// end of bullet
