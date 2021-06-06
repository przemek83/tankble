#include "Powerup.h"

#include <iostream>

#include "../Config.h"

ArmorUp::ArmorUp()
{
    id = 21;
    armor = Config::noArmor;
    source = "image/board/power-up_shield.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 1;
    levelUp = 0;
    speedUp = 0;
    tankUp = 0;
}

bool ArmorUp::canFly() { return true; }

bool ArmorUp::canDrive() { return true; }

SpeedUp::SpeedUp()
{
    id = 22;
    armor = 0;
    source = "image/board/power-up_time.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 0;
    levelUp = 0;
    speedUp = 1;
    tankUp = 0;
}

bool SpeedUp::canFly() { return true; }

bool SpeedUp::canDrive() { return true; }

TankUp::TankUp()
{
    id = 23;
    armor = 0;
    source = "image/board/power-up_life.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 0;
    levelUp = 0;
    speedUp = 0;
    tankUp = 1;
}

bool TankUp::canFly() { return true; }

bool TankUp::canDrive() { return true; }

LevelUp::LevelUp()
{
    id = 24;
    armor = 0;
    source = "image/board/power-up_tank.tga";
    if (!loadBitmap())
        exit(0);
    armorUp = 0;
    levelUp = 1;
    speedUp = 0;
    tankUp = 0;
}

bool LevelUp::canFly() { return true; }

bool LevelUp::canDrive() { return true; }
