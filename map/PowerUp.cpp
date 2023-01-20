#include "PowerUp.h"

PowerUp::PowerUp(unsigned int armor, Coordinates coordinates)
    : Tile(armor, coordinates)
{
}

bool PowerUp::canFly() { return true; }

bool PowerUp::canDrive() { return true; }
