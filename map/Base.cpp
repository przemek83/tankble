#include "Base.h"

Base::Base(Coordinates coordinates) : Tile(MEDIUM_ARMOR, coordinates) {}

bool Base::canFly() { return false; }

bool Base::canDrive() { return false; }

ResourceType Base::getResourceType() const { return ResourceType::BASE; }
