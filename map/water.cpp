#include "water.h"
#include "../config.h"

Water::Water()
{
    this->id = 2;
    this->fly = true;
    this->drive = false;
    this->armor = 0;
    this->source = "image/board/water.tga";
    if (!loadBitmap())
    {
        cout << "Water Error" << std::endl;
        exit(0);
        this->armorUp = 0;
        this->levelUp = 0;
        this->speedUp = 0;
        this->tankUp = 0;
    }
}
