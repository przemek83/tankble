#include "Plant.h"

#include <iostream>

Plant::Plant()
{
    id = 3;
    source = "image/board/plant.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 0;
    levelUp = 0;
    speedUp = 0;
    tankUp = 0;
}

bool Plant::canFly() { return true; }

bool Plant::canDrive() { return true; }
