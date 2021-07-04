#include "Plant.h"

#include <iostream>

Plant::Plant()
{
    id_ = Type::PLANT;
    source_ = "image/board/plant.tga";
    if (!loadBitmap())
        exit(0);
}

bool Plant::canFly() { return true; }

bool Plant::canDrive() { return true; }
