#include "Water.h"

Water::Water(unsigned int x, unsigned int y)
    : Tile(ResourceType::WATER, NO_ARMOR, x, y)
{
}

bool Water::canFly() { return true; }

bool Water::canDrive() { return true; }
