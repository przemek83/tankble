#include "brick.h"
#include <iostream>

Brick::Brick()
{
    id = 1;
    fly = false;
    drive = false;
    armor = 2;
    source = "image/board/brick.tga";
    if (!loadBitmap())
        exit(0);
}
