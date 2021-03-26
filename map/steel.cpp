#include "steel.h"
#include "../config.h"

Steel::Steel()
{
    id = 5;
    fly = false;
    drive = false;
    armor = 100;
    source = "image/board/steel.tga";
    if (!loadBitmap())
    {
        std::cout << "Steel Error" << std::endl;
        exit(0);
    }
}
