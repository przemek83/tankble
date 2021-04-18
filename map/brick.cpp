#include "brick.h"
#include <iostream>

Brick::Brick()
{
    id = 1;
    armor = 2;
    source = "image/board/brick.tga";
    if (!loadBitmap())
        exit(0);
}

bool Brick::canFly() { return false; }

bool Brick::canDrive() { return false; }
