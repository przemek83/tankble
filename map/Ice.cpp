#include "Ice.h"

Ice::Ice() : Tile(ResourceType::ICE, NO_ARMOR) {}

bool Ice::canFly() { return true; }

bool Ice::canDrive() { return true; }
