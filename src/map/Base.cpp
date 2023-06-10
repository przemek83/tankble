#include "Base.h"

Base::Base(Point point) : Tile(MEDIUM_ARMOR, point) {}

bool Base::canFly() { return false; }

bool Base::canDrive() { return false; }

ResourceType Base::getResourceType() const { return ResourceType::BASE; }
