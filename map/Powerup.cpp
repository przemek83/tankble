#include "Powerup.h"

Powerup::Powerup(ResourceType resourceType, int armor)
    : Tile(resourceType, armor)
{
}

bool Powerup::canFly() { return true; }

bool Powerup::canDrive() { return true; }
