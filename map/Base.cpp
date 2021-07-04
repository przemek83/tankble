#include "Base.h"

#include <iostream>

#include <allegro5/allegro.h>

#include "../Player.h"

Base::Base()
{
    id_ = Type::BASE;
    armor_ = Config::mediumArmor;
    source_ = "image/board/base_ok.tga";
    if (!loadBitmap())
        exit(0);
}

bool Base::canFly() { return false; }

bool Base::canDrive() { return false; }
