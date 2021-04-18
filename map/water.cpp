#include "water.h"
#include "../config.h"

Water::Water()
{
    id = 2;
    armor = 0;
    source = "image/board/water.tga";
    if (!loadBitmap())
    {
        std::cout << "Water Error" << std::endl;
        exit(0);
    }
}

bool Water::canFly() { return true; }

bool Water::canDrive() { return true; }
