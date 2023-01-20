#include "PowerUp.h"

PowerUp::PowerUp(ResourceType resourceType, unsigned int armor, unsigned int x,
                 unsigned int y)
    : Tile(resourceType, armor, x, y)
{
}

bool PowerUp::canFly() { return true; }

bool PowerUp::canDrive() { return true; }
