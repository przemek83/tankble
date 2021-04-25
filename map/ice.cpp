#include "ice.h"
#include <iostream>

Ice::Ice()
{
    id = 4;
    source = "image/board/ice.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 0;
    levelUp = 0;
    speedUp = 0;
    tankUp = 0;
}

bool Ice::canFly() { return true; }

bool Ice::canDrive() { return true; }
