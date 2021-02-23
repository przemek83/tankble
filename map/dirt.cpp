#include "dirt.h"
#include <iostream>

Dirt::Dirt()
{
    this->id = 0;
    this->fly = true;
    this->drive = true;
    this->armor = 999;
    this->source = "image/plansza/plansza_zwykle.tga";
    if (!loadBitmap())
    {
        exit(0);
    }
    this->armorUp = 0;
    this->levelUp = 0;
    this->speedUp = 0;
    this->tankUp = 0;
}
