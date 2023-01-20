#include "Base.h"

Base::Base(unsigned int x, unsigned int y)
    : Tile(ResourceType::BASE, MEDIUM_ARMOR, x, y)
{
}

bool Base::canFly() { return false; }

bool Base::canDrive() { return false; }
