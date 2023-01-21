#include "Water.h"

Water::Water(Point point) : Tile(NO_ARMOR, point) {}

bool Water::canFly() { return true; }

bool Water::canDrive() { return true; }

ResourceType Water::getResourceType() const { return ResourceType::WATER; }
