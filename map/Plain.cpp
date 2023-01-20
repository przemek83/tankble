#include "Plain.h"

Plain::Plain(unsigned int x, unsigned int y)
    : Tile(ResourceType::PLAIN, NO_ARMOR, x, y)
{
}

bool Plain::canFly() { return true; }

bool Plain::canDrive() { return true; }
