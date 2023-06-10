#include "Ice.h"

Ice::Ice(Point point) : Tile(NO_ARMOR, point) {}

bool Ice::canFly() { return true; }

bool Ice::canDrive() { return true; }

ResourceType Ice::getResourceType() const { return ResourceType::ICE; }
