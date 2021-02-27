#include "powerup.h"
#include <iostream>

ArmorUp::ArmorUp()
{
    id = 21;
    fly = true;
    drive = true;
    armor = 0;
    source = "image/board/power-up_shield.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 1;
    levelUp = 0;
    speedUp = 0;
    tankUp = 0;
}
SpeedUp::SpeedUp()
{
    id = 22;
    fly = true;
    drive = true;
    armor = 0;
    source = "image/board/power-up_time.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 0;
    levelUp = 0;
    speedUp = 1;
    tankUp = 0;
}
TankUp::TankUp()
{
    id = 23;
    fly = true;
    drive = true;
    armor = 0;
    source = "image/board/power-up_life.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 0;
    levelUp = 0;
    speedUp = 0;
    tankUp = 1;
}
LevelUp::LevelUp()
{
    id = 24;
    fly = true;
    drive = true;
    armor = 0;
    source = "image/board/power-up_tank.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 0;
    levelUp = 1;
    speedUp = 0;
    tankUp = 0;
}
