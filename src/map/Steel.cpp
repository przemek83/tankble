#include "Steel.h"

Steel::Steel(Point point) : Tile(HIGH_ARMOR, point) {}

bool Steel::canFly() { return false; }

bool Steel::canDrive() { return false; }

ResourceType Steel::getResourceType() const { return ResourceType::STEEL; }
