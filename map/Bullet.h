#pragma once

#include "../TankType.h"

class Tank;
struct ALLEGRO_BITMAP;

class Bullet
{
public:
    explicit Bullet(Tank*);
    ~Bullet();

    Bullet& operator=(const Bullet& other) = delete;
    Bullet(const Bullet& other) = delete;

    Bullet& operator=(Bullet&& other) = delete;
    Bullet(Bullet&& other) = delete;

    ALLEGRO_BITMAP* display() const;
    TankType getTankType() const;
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
    Tank* vehicle_{nullptr};
    int direction_;
    int speed_;
    int power_;
    int x_;
    int y_;
};
