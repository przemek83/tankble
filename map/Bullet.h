#pragma once

#include <allegro5/allegro.h>
#include "../Vehicle.h"

class Bullet
{
public:
    explicit Bullet(Vehicle*);
    ~Bullet();

    Bullet& operator=(const Bullet& other) = delete;
    Bullet(const Bullet& other) = delete;

    Bullet& operator=(Bullet&& other) = delete;
    Bullet(Bullet&& other) = delete;

    ALLEGRO_BITMAP* display();
    int getId() const;
    int getPower() const;
    int getSpeed() const;
    int getDirection() const;
    int getX() const;
    int getY() const;

    int getCenterX() const;
    int getCenterY() const;
    void setX(int newX);
    void setY(int newY);
    int getDirectionX() const;
    int getDirectionY() const;

private:
    bool loadBitmap();

    ALLEGRO_BITMAP* bmp_{nullptr};
    const char* source_{nullptr};
    Vehicle* vehicle_{nullptr};
    int id_;
    int direction_;
    int speed_;
    int power_;
    int x_;
    int y_;
};
