#include "Brick.h"

#include <iostream>

#include "../Config.h"

Brick::Brick()
{
    id_ = Type::BRICK;
    armor_ = Config::lowArmor;
    source_ = "image/board/brick.tga";
    if (!loadBitmap())
        exit(0);
}

bool Brick::canFly() { return false; }

bool Brick::canDrive() { return false; }
