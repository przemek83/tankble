#include "base.h"

#include <iostream>

#include <allegro5/allegro.h>

#include "../player.h"

Base::Base()
{
    id = 6;
    armor = Config::mediumArmor;
    source = "image/board/base_ok.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 0;
    levelUp = 0;
    speedUp = 0;
    tankUp = 0;
}

bool Base::canFly() { return false; }

bool Base::canDrive() { return false; }
