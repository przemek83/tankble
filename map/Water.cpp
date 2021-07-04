#include "Water.h"

#include "../Config.h"

Water::Water()
{
    id_ = Type::WATER;
    armor_ = Config::noArmor;
    source_ = "image/board/water.tga";
    if (!loadBitmap())
    {
        std::cout << "Water Error" << std::endl;
        exit(0);
    }
}

bool Water::canFly() { return true; }

bool Water::canDrive() { return true; }
