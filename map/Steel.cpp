#include "Steel.h"

Steel::Steel(unsigned int x, unsigned int y) : Tile(HIGH_ARMOR, x, y) {}

bool Steel::canFly() { return false; }

bool Steel::canDrive() { return false; }

ResourceType Steel::getResourceType() const { return ResourceType::STEEL; }
