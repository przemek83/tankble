#include "Water.h"

Water::Water(unsigned int x, unsigned int y) : Tile(NO_ARMOR, x, y) {}

bool Water::canFly() { return true; }

bool Water::canDrive() { return true; }

ResourceType Water::getResourceType() const { return ResourceType::WATER; }
