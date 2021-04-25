#include "brick.h"

#include <iostream>

#include "../config.h"

Brick::Brick()
{
    id = 1;
    armor = Config::lowArmor;
    source = "image/board/brick.tga";
    if (!loadBitmap())
        exit(0);
}

bool Brick::canFly() { return false; }

bool Brick::canDrive() { return false; }
