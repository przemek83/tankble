#include "plain.h"
#include <iostream>

Plain::Plain()
{
    id = 0;
    fly = true;
    drive = true;
    armor = 999;
    source = "image/board/plain.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 0;
    levelUp = 0;
    speedUp = 0;
    tankUp = 0;
}
