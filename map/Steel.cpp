#include "Steel.h"

#include "../Config.h"

Steel::Steel()
{
    id_ = Type::STEEL;
    armor_ = Config::highArmor;
    source_ = "image/board/steel.tga";
    if (!loadBitmap())
    {
        std::cout << "Steel Error" << std::endl;
        exit(0);
    }
}

bool Steel::canFly() { return false; }

bool Steel::canDrive() { return false; }
