#include "Ice.h"

#include "../Config.h"

Ice::Ice() : Tile(ResourceType::ICE, Config::noArmor) {}

bool Ice::canFly() { return true; }

bool Ice::canDrive() { return true; }
