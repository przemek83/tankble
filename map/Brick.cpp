#include "Brick.h"

Brick::Brick(unsigned int x, unsigned int y)
    : Tile(ResourceType::BRICK, LOW_ARMOR, x, y)
{
}

bool Brick::canFly() { return false; }

bool Brick::canDrive() { return false; }
