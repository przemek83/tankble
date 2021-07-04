#include "Powerup.h"

#include <iostream>

#include "../Config.h"

ArmorUp::ArmorUp()
{
    id_ = Type::ARMOR_UP;
    armor_ = Config::noArmor;
    source_ = "image/board/power-up_shield.tga";
    if (!loadBitmap())
        exit(0);
}

bool ArmorUp::canFly() { return true; }

bool ArmorUp::canDrive() { return true; }

SpeedUp::SpeedUp()
{
    id_ = Type::SPEED_UP;
    armor_ = 0;
    source_ = "image/board/power-up_time.tga";
    if (!loadBitmap())
        exit(0);
}

bool SpeedUp::canFly() { return true; }

bool SpeedUp::canDrive() { return true; }

TankUp::TankUp()
{
    id_ = Type::TANK_UP;
    armor_ = 0;
    source_ = "image/board/power-up_life.tga";
    if (!loadBitmap())
        exit(0);
}

bool TankUp::canFly() { return true; }

bool TankUp::canDrive() { return true; }

LevelUp::LevelUp()
{
    id_ = Type::LEVEL_UP;
    armor_ = 0;
    source_ = "image/board/power-up_tank.tga";
    if (!loadBitmap())
        exit(0);
}

bool LevelUp::canFly() { return true; }

bool LevelUp::canDrive() { return true; }
