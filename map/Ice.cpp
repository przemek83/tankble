#include "Ice.h"

Ice::Ice(unsigned int x, unsigned int y) : Tile(NO_ARMOR, x, y) {}

bool Ice::canFly() { return true; }

bool Ice::canDrive() { return true; }

ResourceType Ice::getResourceType() const { return ResourceType::ICE; }
