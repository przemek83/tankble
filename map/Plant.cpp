#include "Plant.h"

Plant::Plant(unsigned int x, unsigned int y)
    : Tile(ResourceType::PLANT, NO_ARMOR, x, y)
{
}

bool Plant::canFly() { return true; }

bool Plant::canDrive() { return true; }

bool Plant::isPartOfBackground() { return false; }
