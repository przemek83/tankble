#include "PowerUp.h"

PowerUp::PowerUp(ResourceType resourceType, int armor)
    : Tile(resourceType, armor)
{
}

bool PowerUp::canFly() { return true; }

bool PowerUp::canDrive() { return true; }
