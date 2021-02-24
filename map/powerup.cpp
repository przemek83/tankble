#include "powerup.h"
#include <iostream>

ArmorUp::ArmorUp()
{
    this->id = 21;
    this->fly = true;
    this->drive = true;
    this->armor = 0;
    this->source = "image/plansza/pwrup_lopata.tga";
    if (!loadBitmap())
    {
        // cout << "Bricks Error" << "\n";
        exit(0);
    }
    this->armorUp = 1;
    this->levelUp = 0;
    this->speedUp = 0;
    this->tankUp = 0;
}
SpeedUp::SpeedUp()
{
    this->id = 22;
    this->fly = true;
    this->drive = true;
    this->armor = 0;
    this->source = "image/plansza/pwrup_czas.tga";
    if (!loadBitmap())
    {
        // cout << "Bricks Error" << "\n";
        exit(0);
    }
    this->armorUp = 0;
    this->levelUp = 0;
    this->speedUp = 1;
    this->tankUp = 0;
}
TankUp::TankUp()
{
    this->id = 23;
    this->fly = true;
    this->drive = true;
    this->armor = 0;
    this->source = "image/board/power-up_life.tga";
    if (!loadBitmap())
    {
        // cout << "Bricks Error" << "\n";
        exit(0);
    }
    this->armorUp = 0;
    this->levelUp = 0;
    this->speedUp = 0;
    this->tankUp = 1;
}
LevelUp::LevelUp()
{
    this->id = 24;
    this->fly = true;
    this->drive = true;
    this->armor = 0;
    this->source = "image/board/power-up_tank.tga";
    if (!loadBitmap())
    {
        //		cout << "Bricks Error" << "\n";
        exit(0);
    }
    this->armorUp = 0;
    this->levelUp = 1;
    this->speedUp = 0;
    this->tankUp = 0;
}
