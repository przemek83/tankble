#include "base.h"
#include <allegro5/allegro.h>
#include <iostream>
#include "../player.h"

using std::cout;

Base::Base()
{
    this->id = 6;
    this->fly = false;
    this->drive = false;
    this->armor = 10;
    this->source = "image/board/plain.tga";
    if (!loadBitmap())
    {
        exit(0);
    }
    this->armorUp = 0;
    this->levelUp = 0;
    this->speedUp = 0;
    this->tankUp = 0;
}
