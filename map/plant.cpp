#include <iostream>
#include "plant.h"

Plant::Plant()
{
    this->id = 3;
    this->fly = true;
    this->drive = true;
    this->armor = 999;
    this->source = "image/board/plant.tga";
    if (!loadBitmap())
    {
        exit(0);
    }
    this->armorUp = 0;
    this->levelUp = 0;
    this->speedUp = 0;
    this->tankUp = 0;
}
