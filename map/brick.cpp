#include "brick.h"
#include <iostream>

Brick::Brick()
{
    this->id = 1;
    this->fly = false;
    this->drive = false;
    this->armor = 2;
    this->source = "image/board/brick.tga";
    if (!loadBitmap())
    {
        exit(0);
        this->armorUp = 0;
        this->levelUp = 0;
        this->speedUp = 0;
        this->tankUp = 0;
    }
}