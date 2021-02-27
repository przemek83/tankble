#include "water.h"
#include "../config.h"

Water::Water()
{
    id = 2;
    fly = true;
    drive = false;
    armor = 0;
    source = "image/board/water.tga";
    if (!loadBitmap())
    {
        cout << "Water Error" << std::endl;
        exit(0);
    }
}
