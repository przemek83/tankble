#include "steel.h"
#include "../config.h"

Steel::Steel()
{
    id = 5;
    armor = 100;
    source = "image/board/steel.tga";
    if (!loadBitmap())
    {
        std::cout << "Steel Error" << std::endl;
        exit(0);
    }
}

bool Steel::canFly() { return false; }

bool Steel::canDrive() { return false; }
