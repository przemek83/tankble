#include "Water.h"

#include "../Config.h"

Water::Water() : Tile(ResourceType::WATER, Config::noArmor) {}

bool Water::canFly() { return true; }

bool Water::canDrive() { return true; }
