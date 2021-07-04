#pragma once

#include <iostream>

#include <allegro5/allegro.h>

#include "../Config.h"

class Tile
{
public:
    Tile() = default;
    virtual ~Tile();

    Tile& operator=(const Tile& other) = delete;
    Tile(const Tile& other) = delete;

    Tile& operator=(Tile&& other) = delete;
    Tile(Tile&& other) = delete;

    virtual bool canFly() = 0;
    virtual bool canDrive() = 0;
    virtual bool destroy(int);
    virtual ALLEGRO_BITMAP* display();  // return bitmap 30x30

    enum class Type : unsigned int
    {
        PLAIN = 0,
        BRICK,
        WATER,
        PLANT,
        ICE,
        STEEL,
        BASE,
        ARMOR_UP,
        SPEED_UP,
        TANK_UP,
        LEVEL_UP
    };

    bool isPowerUp() const;

    Type getId() const;

protected:
    virtual bool loadBitmap();

    ALLEGRO_BITMAP* bmp_;
    const char* source_;
    int armor_{Config::maxArmor};
    Type id_;
};
