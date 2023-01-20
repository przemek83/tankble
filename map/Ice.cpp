#include "Ice.h"

Ice::Ice(Coordinates coordinates) : Tile(NO_ARMOR, coordinates) {}

bool Ice::canFly() { return true; }

bool Ice::canDrive() { return true; }

ResourceType Ice::getResourceType() const { return ResourceType::ICE; }
