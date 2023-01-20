#include "PowerUp.h"

PowerUp::PowerUp(unsigned int armor, unsigned int x, unsigned int y)
    : Tile(armor, x, y)
{
}

bool PowerUp::canFly() { return true; }

bool PowerUp::canDrive() { return true; }
