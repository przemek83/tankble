#include "Steel.h"

Steel::Steel(Coordinates coordinates) : Tile(HIGH_ARMOR, coordinates) {}

bool Steel::canFly() { return false; }

bool Steel::canDrive() { return false; }

ResourceType Steel::getResourceType() const { return ResourceType::STEEL; }
