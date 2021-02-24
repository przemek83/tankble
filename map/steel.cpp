#include "steel.h"
#include "../config.h"

Steel::Steel()
{
    this->id = 5;
    this->fly = false;
    this->drive = false;
    this->armor = 100;
    this->source = "image/board/steel.tga";
    if (!loadBitmap())
    {
        cout << "Steel Error"
             << "\n";
        exit(0);
    }
    this->armorUp = 0;
    this->levelUp = 0;
    this->speedUp = 0;
    this->tankUp = 0;
}
