#include "Ice.h"

Ice::Ice(unsigned int x, unsigned int y)
    : Tile(ResourceType::ICE, NO_ARMOR, x, y)
{
}

bool Ice::canFly() { return true; }

bool Ice::canDrive() { return true; }
