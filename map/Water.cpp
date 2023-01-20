#include "Water.h"

Water::Water(Coordinates coordinates) : Tile(NO_ARMOR, coordinates) {}

bool Water::canFly() { return true; }

bool Water::canDrive() { return true; }

ResourceType Water::getResourceType() const { return ResourceType::WATER; }
