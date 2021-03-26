#pragma once

#include <allegro5/allegro.h>

class Tile
{
public:
    Tile() = default;
    virtual ~Tile();

    Tile& operator=(const Tile& other) = delete;
    Tile(const Tile& other) = delete;

    Tile& operator=(Tile&& other) = delete;
    Tile(Tile&& other) = delete;

    virtual bool canFly();
    virtual bool canDrive();
    virtual bool destroy(int);
    virtual ALLEGRO_BITMAP* display();  // return bitmap 30x30
    virtual int getId();
    int getArmorUp();
    int getLevelUp();
    int getSpeedUp();
    int getTankUp();

protected:
    virtual bool loadBitmap();

    ALLEGRO_BITMAP* bmp;
    const char* source;
    int armor;
    int id;
    int armorUp;
    int levelUp;
    int speedUp;
    int tankUp;
    bool fly;
    bool drive;
};
