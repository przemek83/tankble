#include "Water.h"

Water::Water(Point point) : Tile(NO_ARMOR, point) {}

bool Water::canFly() { return true; }

bool Water::canDrive() { return false; }

ResourceType Water::getResourceType() const { return ResourceType::WATER; }
