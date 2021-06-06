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
    virtual int getId();
    int getArmorUp() const;
    int getLevelUp() const;
    int getSpeedUp() const;
    int getTankUp() const;

protected:
    virtual bool loadBitmap();

    ALLEGRO_BITMAP* bmp;
    const char* source;
    int armor{Config::maxArmor};
    int id;
    int armorUp;
    int levelUp;
    int speedUp;
    int tankUp;
};
