#include "plain.h"
#include <iostream>

Plain::Plain()
{
    id = 0;
    armor = 999;
    source = "image/board/plain.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 0;
    levelUp = 0;
    speedUp = 0;
    tankUp = 0;
}

bool Plain::canFly() { return true; }

bool Plain::canDrive() { return true; }
