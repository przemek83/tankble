#include "base.h"
#include <allegro5/allegro.h>
#include <iostream>
#include "../player.h"

using std::cout;

Base::Base()
{
    id = 6;
    fly = false;
    drive = false;
    armor = 10;
    source = "image/board/base_ok.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 0;
    levelUp = 0;
    speedUp = 0;
    tankUp = 0;
}
